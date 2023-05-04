#ifndef TRADUNGEON_MARKET_H
#define TRADUNGEON_MARKET_H

#include <map>
#include <vector>
#include <optional>
#include <exception>

namespace tradungeon
{

// template<typename T>
// using MinQueue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
// template<typename T>
// using MaxQueue = std::priority_queue<T>;

enum class OrderType { Buy, Sell };

struct Order
{
    OrderType m_type;
    int m_user_id;
    int m_item_id;
    int m_quantity;
    int m_price;
};

// OrderQueue is a priority queue for buy or sell orders.
// Most expensive buy order and cheapest sell order comes first.
class OrderQueue
{
public:
    const std::vector<Order>& get_queue() const;

    void push(Order order);
    Order pop();
    Order top() const;

    bool is_empty() const;

    // Given an opposite type of order,
    // check if there is a matching order waiting in the queue.
    bool is_contract_possible(Order order) const;

private:
    bool is_sorted(Order lhs, Order rhs);

    std::vector<Order> m_queue;
};

// Contract is a trade where buyer and seller are both satisfied with the price they proposed.
// It is made when a buyer is willing to spend more money
// than what a seller registered to a market, or vice-versa.
//
// For example, if A wants to buy an apple for 10 gold and B wants to sell it for 8 gold,
// both will agree to trade the apple for a price between 8~10.
struct Contract
{
    Order m_buy_order;
    Order m_sell_order;
};

class Market
{
public:
    const std::vector<Order>& get_buy_queue(int item_id) const;
    const std::vector<Order>& get_sell_queue(int item_id) const;

    // Add an order to buy or sell queue.
    // If the order can be fulfilled, returns corresponding contract.
    // Buy order with highest price and sell order with lowest price have highest priority.
    //
    // Minor note: if OrderQueue didn't exist for this item, a new one is automatically generated.
    std::optional<Contract> register_order(Order order);

private:
    Contract establish_contract(Order buy_order, Order sell_order);

    std::map<int, OrderQueue> m_buy_queue;
    std::map<int, OrderQueue> m_sell_queue;
};

} // namespace tradungeon

#endif
