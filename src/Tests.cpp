#include "Tests.h"
#include "Console.h"
#include "Random.h"
#include "UIManager.h"
#include "MessageLogViewer.h"
#include <iostream>
#include <numeric>

namespace tradungeon::test
{

TestUI::TestUI(const Viewport& viewport)
    : UI(viewport)
{}

void TestUI::onRender(Console& console)
{
    renderChar(console, '@', {0, 0});
    renderString(console, "hahahoho", {{1,1},{3,3}});
}

void test_random()
{
    for(int i=0;i<100;++i)
    {
        std::cout << Random::range(0, 4);
    }

    auto sample = Random::sample(std::vector{11,22,33,44,55}, 3);
    Random::shuffle(sample);

    std::cout << "\n";
    for (auto s : sample)
    {
        std::cout << s << " ";
    }
    std::cout << "\n";
}

void test_console()
{
    auto console = Console({20, 10});
    console.renderChar('#', {0, 0});
    console.renderChar('#', {19, 0});
    console.renderChar('#', {0, 9});
    console.renderChar('#', {19, 9});
    console.print();

    console.renderChar('@', {19, 9});
    console.print();

    console.renderString("hello, world!\nnewline test\n\nnewline test newline test newline test", {{4, 2}, {15, 5}});
    console.print();
}

void test_market()
{
    auto order_list = std::vector<Order>{
        {OrderType::Buy, 0, 0, 10, 55},
        {OrderType::Buy, 0, 1, 3, 100},
        {OrderType::Sell, 1, 0, 7, 50},
        {OrderType::Sell, 2, 0, 5, 45},
        {OrderType::Buy, 1, 0, 1, 47},
    };

    auto name_dict = std::map<int, std::string>{
        {0, "John"},
        {1, "Peter"},
        {2, "Harry"},
    };

    auto item_dict = std::map<int, std::string>{
        {0, "Apple"},
        {1, "Lemon"},
    };

    auto market = Market{};

    for (auto order : order_list)
    {
        std::cout << "Processing order...\n\n";
        if (auto result = market.register_order(order); result.has_value())
        {
            std::cout << "[Contract]\n";
            std::cout << "buyer: " << name_dict[result->m_buy_order.m_user_id] << "\n";
            std::cout << "seller: " << name_dict[result->m_sell_order.m_user_id] << "\n";
            std::cout << "item: " << item_dict[result->m_buy_order.m_item_id] << "\n";
            std::cout << "quantity: " << result->m_buy_order.m_quantity << "\n";
            std::cout << "price range: " << result->m_sell_order.m_price << " ~ " << result->m_buy_order.m_price << "\n\n";
        }
    }

    for (auto [user_id, name] : name_dict)
    {
        auto remaining_orders = market.get_user_orders(user_id);
        for (auto order : remaining_orders)
        {
            std::cout << "[Remaining order]\n";
            std::cout << "buyer: " << name << "\n";
            std::cout << "type: " << (order.m_type == OrderType::Buy ? "Buy" : "Sell") << "\n";
            std::cout << "item: " << item_dict[order.m_item_id] << "\n";
            std::cout << "quantity: " << order.m_quantity << "\n";
            std::cout << "price: " << order.m_price << "\n\n";
        }
    }
}


void test_price_fluctuation()
{
    // Initial settings
    auto simulator = MarketSimulator{};
    simulator.m_items = {
        {11, "Lemon", 100, 30, 30, 70},
        {44, "Apple", 200, 30, 30, 10},
    };
    simulator.m_users = {
        {1234, "Jenny"},
        {7777, "Robert"},
        {5678, "Jackson"},
        {3579, "David"},
        {2684, "Laura"},
    };

    // Randomize item preference.
    for (auto& item : simulator.m_items)
    {
        // Select 4 random users
        auto selected = Random::sample(simulator.m_users, 4);
        Random::shuffle(selected);

        // Make an item preference for each one
        auto preferences = std::vector<Preference>{};
        for (const auto& user : selected)
        {
            auto pref = Preference{};
            pref.m_user_id = user.m_id;
            pref.m_degree = Random::range(50, 100);
            pref.m_desired_price = item.m_initial_price + Random::range(-20, 20);

            preferences.push_back(pref);

            // std::cout << user.m_name << " wants to trade " << item.m_name << " at " << pref.m_desired_price << " with degree of " << pref.m_degree << "\n";
        }

        // First two will buy the item, while the others sell.
        item.m_buyers.insert(item.m_buyers.end(), preferences.begin(), preferences.begin() + 2);
        item.m_sellers.insert(item.m_sellers.end(), preferences.begin() + 2, preferences.end());
    }

    // Simulate 10 days of market trade
    for (int day = 0; day < 50; ++day)
    {
        if (day == 25)
        {
            simulator.m_items[0].m_desired_net_demand -= 30;
            simulator.m_items[1].m_desired_net_demand += 30;
        }

        std::cout << "[day " << day << "]\n\n";

        for (auto& item : simulator.m_items)
        {
            auto orders = std::vector<Order>{};

            // Prepare buy orders
            double total_demand_degree = std::accumulate(item.m_buyers.begin(), item.m_buyers.end(), 0.0, [](auto sum, auto pref){ return sum + pref.m_degree; });
            for (auto& pref : item.m_buyers)
            {
                auto order = Order{};
                order.m_type = OrderType::Buy;
                order.m_item_id = item.m_id;
                order.m_user_id = pref.m_user_id;
                order.m_price = pref.m_desired_price;
                order.m_quantity = item.m_net_demand * pref.m_degree / total_demand_degree;

                orders.push_back(order);
            }

            // Prepare sell orders
            double total_supply_degree = std::accumulate(item.m_sellers.begin(), item.m_sellers.end(), 0.0, [](auto sum, auto pref){ return sum + pref.m_degree; });
            for (auto& pref : item.m_sellers)
            {
                auto order = Order{};
                order.m_type = OrderType::Sell;
                order.m_item_id = item.m_id;
                order.m_user_id = pref.m_user_id;
                order.m_price = pref.m_desired_price;
                order.m_quantity = item.m_net_supply * pref.m_degree / total_supply_degree;

                orders.push_back(order);
            }

            // Simulate trade
            simulator.m_market.clear_orders();

            Random::shuffle(orders);
            for (auto order : orders)
            {
                std::cout << (order.m_type == OrderType::Buy ? "Buy " : "Sell ") << order.m_quantity << " " << item.m_name << " for " << order.m_price << std::endl;
                if (auto result = simulator.m_market.register_order(order); result.has_value())
                {
                    std::cout << order.m_quantity << " " << item.m_name << " were " << (order.m_type == OrderType::Buy ? "bought" : "sold") << " for " << result->m_sell_order.m_price << " gold" << std::endl;
                }
            }

            // Adjust desired price
            for (auto& pref : item.m_sellers)
            {
                auto remaining_orders = simulator.m_market.get_user_orders(pref.m_user_id);
                if (remaining_orders.size() > 0)
                {
                    pref.m_desired_price -= Random::range(1, 5);
                }
                else
                {
                    pref.m_desired_price += Random::range(1, 5);
                }
            }
            for (auto& pref : item.m_buyers)
            {
                auto remaining_orders = simulator.m_market.get_user_orders(pref.m_user_id);
                if (remaining_orders.size() > 0)
                {
                    pref.m_desired_price += Random::range(1, 5);
                }
                else
                {
                    pref.m_desired_price -= Random::range(1, 5);
                }
            }

            // Check unresolved net supply and demand
            auto unresolved_supplies = simulator.m_market.get_sell_queue(item.m_id);
            auto net_unresolved_supply = std::accumulate(unresolved_supplies.begin(), unresolved_supplies.end(), 0, [](auto sum, auto order){ return sum + order.m_quantity; });
            std::cout << "Unresolved supply: " << net_unresolved_supply << " / " << item.m_net_supply << std::endl;

            auto unresolved_demands = simulator.m_market.get_buy_queue(item.m_id);
            auto net_unresolved_demand = std::accumulate(unresolved_demands.begin(), unresolved_demands.end(), 0, [](auto sum, auto order){ return sum + order.m_quantity; });
            std::cout << "Unresolved demand: " << net_unresolved_demand << " / " << item.m_net_demand << std::endl;

            // Adjust net supply and demand up to 1~10% of the difference
            auto extra_supply = net_unresolved_supply - net_unresolved_demand;
            item.m_net_supply -= extra_supply * Random::range(1, 10) / 100;

            // Force net demand to reach desired level
            item.m_net_demand += (item.m_desired_net_demand - item.m_net_demand) * 4 / 10;

            std::cout << std::endl;
            // break; // Test with only one item for now.
        }
    }
}

void test_ui()
{
    auto console = Console({80, 25});
    auto ui_manager = UIManager();
    ui_manager.push(std::make_shared<TestUI>(Viewport{{0, 0}, {80, 25}}));
    ui_manager.push(std::make_shared<TestUI>(Viewport{{5, 10}, {5, 5}}));
    ui_manager.render(console);
    ui_manager.pop();
    ui_manager.render(console);
}

void test_message_log()
{
    auto log = MessageLog({20, 5});
    log.push("Hi");
    log.push("Hello, World!");
    log.push("A very long string that overflows");
    std::cout << log.size() << std::endl;
    std::cout << log.getLines(0, 3);

    log.push("asdf");
    log.push("asdf");
    log.push("asdf");
    log.push("asdf");
    std::cout << log.size() << std::endl;
    std::cout << log.getLines(0, 3);
}

void test_message_log_viewer()
{
    auto console = Console({80, 5});
    auto ui_manager = UIManager();
    auto msg_viewer = std::make_shared<MessageLogViewer>(Viewport{{0, 0}, {80, 5}}, 20);

    ui_manager.push(msg_viewer);
    ui_manager.render(console);

    msg_viewer->push("Single Line");
    ui_manager.render(console);

    msg_viewer->scrollDown();
    ui_manager.render(console);

    msg_viewer->scrollUp();
    ui_manager.render(console);

    for (int i=0;i<10;++i)
    {
        msg_viewer->push("Hello, World!" + std::to_string(i));
    }
    ui_manager.render(console);

    msg_viewer->scrollUp();
    msg_viewer->scrollUp();
    ui_manager.render(console);
}

} // namespace tradungeon::test
