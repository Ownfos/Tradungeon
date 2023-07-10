#include "MarketSimulator.h"

namespace tradungeon
{

MarketSimulator::MarketSimulator(const std::vector<std::shared_ptr<Trader>>& traders)
    : m_traders(traders)
{}

void MarketSimulator::addItem(const ItemConfig& item_config)
{
    m_item_configs.push_back(item_config);

    // Select random people.
    auto selected = Random::sample(m_traders, item_config.m_num_buyers + item_config.m_num_sellers);
    Random::shuffle(selected);

    auto buyer_shares = generateMarketShare(item_config.m_num_buyers, 50, 100);
    auto seller_shares = generateMarketShare(item_config.m_num_sellers, 50, 100);

    for (int i = 0; i < selected.size(); ++i)
    {
        // Decide the price and quantity.
        auto trader_config = TraderConfig{};
        trader_config.m_trader = selected[i];
        trader_config.m_desired_price = item_config.m_initial_price + Random::range(-20, 20);

        // People on the front are assigned as buyers,
        // while the others become sellers.
        if (i < item_config.m_num_buyers)
        {
            trader_config.m_market_share = buyer_shares[i];
            m_item_configs.back().m_buyer_configs.push_back(trader_config);
        }
        else
        {
            // Note: the first seller's index in 'selected' is 'item_config.m_num_buyers',
            // thus we need 'i - item_config.m_num_buyers' in order to access seller_shares[0].
            trader_config.m_market_share = seller_shares[i - item_config.m_num_buyers];
            m_item_configs.back().m_seller_configs.push_back(trader_config);
        }
    }
}

void MarketSimulator::generateDailyOrders()
{
    executeRemainingOrders();

    for (auto& item_config : m_item_configs)
    {
        adjustDesiredPrice(item_config);
        adjustSupplyAndDemand(item_config);
        assignOrders(item_config);
    }

    m_market.clear_orders();
}

std::vector<double> MarketSimulator::generateMarketShare(int num_people, double min, double max)
{
    // Generate a random value list.
    auto result = std::vector<double>();
    std::generate_n(std::back_inserter(result), num_people, [=]{
        return Random::range(min, max);
    });

    // Normalize the values so that the sum becomes 1.
    auto sum = std::accumulate(result.begin(), result.end(), 0.0);
    for (auto& e : result)
    {
        e /= sum;
    }

    return result;
}

void MarketSimulator::executeRemainingOrders()
{
    for (auto& trader : m_traders)
    {
        for (const auto& order : trader->remainingOrders())
        {
            m_market.register_order(order);
        }
        trader->clearOrders();
    }
}

void MarketSimulator::adjustDesiredPrice(ItemConfig& item_config)
{
    const auto item_id = item_config.m_item->id();

    // Returns true when there are no remaining orders registered by this person.
    // This means that the trader managed to buy/sell desired quantity.
    auto is_order_successful = [](const std::vector<Order>& remaining_orders, int trader_id){
        auto is_id_same = [&](const Order& order){
            return order.m_user_id == trader_id;
        };
        auto it = std::find_if(remaining_orders.begin(), remaining_orders.end(), is_id_same);

        return it == remaining_orders.end();
    };

    // Buyers will decrase desired price when they succeed
    const auto& buy_queue = m_market.get_buy_queue(item_id);
    for (auto& buyer_config : item_config.m_buyer_configs)
    {
        if (is_order_successful(buy_queue, buyer_config.m_trader->id()))
        {
            buyer_config.m_desired_price -= Random::range(1, 5);
        }
        else
        {
            buyer_config.m_desired_price += Random::range(1, 5);
        }
    }

    // Sellers will increase desired price when they succeed
    const auto& sell_queue = m_market.get_sell_queue(item_id);
    for (auto& seller_config : item_config.m_seller_configs)
    {
        if (is_order_successful(sell_queue, seller_config.m_trader->id()))
        {
            seller_config.m_desired_price += Random::range(1, 5);
        }
        else
        {
            seller_config.m_desired_price -= Random::range(1, 5);
        }
    }
}

void MarketSimulator::adjustSupplyAndDemand(ItemConfig& item_config)
{
    auto item_id = item_config.m_item->id();
    auto accumulate_quantity = [](const std::vector<Order>& orders){
        return std::accumulate(orders.begin(), orders.end(), 0, [](int sum, const Order& order){ return sum + order.m_quantity; });
    };

    auto unresolved_supply = accumulate_quantity(m_market.get_sell_queue(item_id));
    auto unresolved_demand = accumulate_quantity(m_market.get_buy_queue(item_id));
    auto excess_supply = unresolved_supply - unresolved_demand;

    // Apply the rule of supply and demand
    item_config.m_net_supply -= clamp(1, excess_supply / 3, Random::range(1, 10));
    item_config.m_net_demand += clamp(1, excess_supply / 3, Random::range(1, 10));
}

void MarketSimulator::assignOrders(ItemConfig& item_config)
{
    for (auto& buyer_config : item_config.m_buyer_configs)
    {
        auto order = Order{};
        order.m_type = OrderType::Buy;
        order.m_item_id = item_config.m_item->id();
        order.m_user_id = buyer_config.m_trader->id();
        order.m_price = buyer_config.m_desired_price;
        order.m_quantity = std::round(item_config.m_net_demand * buyer_config.m_market_share);

        buyer_config.m_trader->pushOrder(order);
    }

    for (auto& seller_config : item_config.m_seller_configs)
    {
        auto order = Order{};
        order.m_type = OrderType::Sell;
        order.m_item_id = item_config.m_item->id();
        order.m_user_id = seller_config.m_trader->id();
        order.m_price = seller_config.m_desired_price;
        order.m_quantity = std::round(item_config.m_net_supply * seller_config.m_market_share);

        seller_config.m_trader->pushOrder(order);
    }
}

} // namespace tradungeon
