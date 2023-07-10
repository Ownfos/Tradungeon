#ifndef TRADUNGEON_MARKET_SIMULATOR_H
#define TRADUNGEON_MARKET_SIMULATOR_H

#include "Market.h"
#include "Random.h"
#include "interactable/Item.h"
#include <vector>
#include <memory>
#include <map>
#include <numeric>

namespace tradungeon
{

class Trader : private Polymorphic
{
public:
    virtual int id() const = 0;
    virtual const std::vector<Order>& remainingOrders() const = 0;
    virtual void pushOrder(const Order& order) = 0;
    virtual void clearOrders() = 0;
};

struct TraderConfig
{
    std::shared_ptr<Trader> m_trader;
    int m_desired_price;
    double m_market_share;
};

struct ItemConfig
{
    std::shared_ptr<Item> m_item;
    int m_net_demand;
    int m_net_supply;
    int m_initial_price;
    int m_num_buyers;
    int m_num_sellers;
    std::vector<TraderConfig> m_buyer_configs;
    std::vector<TraderConfig> m_seller_configs;
};

// Controls which item should an NPC buy or sell.
// Buy applying the rule of supply and demand,
// the price of each item will fluctuate as if it were a free market.
//
// The trading algorithm works in following order:
// 1. assign buy/sell orders to each NPC at the beginning of each day
// 2. player interacts with NPC to make contracts
// 3. let npcs trade with each other right before proceeding to the next day
// 4. unaccomplished orders affect the total demand, supply, and price of each item.
class MarketSimulator
{
public:
    MarketSimulator(const std::vector<std::shared_ptr<Trader>>& traders);

    // Let the NPCs trade this item.
    // According to the given setting, buyers and sellers will be chosen.
    void addItem(const ItemConfig& item_config);

    void generateDailyOrders();

private:
    // Creates a list of random numbers in range [0, 1] that sums up to 1.
    // This is used to decide the portion of net supply/demand a trader is responsible for.
    // For example, [0.5, 0.3, 0.2] means that the first person is in charge of half of the items on the market.
    std::vector<double> generateMarketShare(int num_people, double min, double max);

    // Let the NPCS trade with each other.
    void executeRemainingOrders();

    // Each NPC has a desired price for each item.
    // They will invest more money if they fail to get what they want.
    void adjustDesiredPrice(ItemConfig& item_config);
    
    void adjustSupplyAndDemand(ItemConfig& item_config);

    void assignOrders(ItemConfig& item_config);

    Market m_market;
    std::vector<ItemConfig> m_item_configs;
    std::vector<std::shared_ptr<Trader>> m_traders;
};

} // namespace tradungeon

#endif
