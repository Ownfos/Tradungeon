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
//
// The reason for not using std::priority_queue is that we need
// a random access to every elements in the list
// so that player can know how much it will cost to trade desired quantity.
//
// Note that the game's market will be much smaller than real-life stock markets.
// This makes current market price for each item quite unstable,
// due to small quantity assigned per each order.
// For example, you wan't to buy three apple but there are only two cheapest apples available.
// In such case, you will be interested in the second-cheapest apple's information as well as the cheapest.
class OrderQueue
{
public:
    const std::vector<Order>& get_queue() const;

    void push(Order order);
    Order pop();
    const Order& top() const;

    bool is_empty() const;

    std::vector<Order>::const_iterator begin() const;
    std::vector<Order>::const_iterator end() const;

    size_t size() const;
    Order operator[](int index) const;

    // Given an opposite type of order,
    // check if there is a matching order waiting in the queue.
    bool is_contract_possible(const Order& order) const;

private:
    bool is_sorted(const Order& lhs, const Order& rhs);

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

// Market is a simulator that manages buy and sell Orders.
// If possible, a pair of buy-sell orders (a Contract!) is produced.
// It also provides getter functions that allows you to see the waitlist in details.
class Market
{
public:
    // Note: an empty queue is returned if there are no pending Orders (thereby non-const getter).
    const std::vector<Order>& get_buy_queue(int item_id);
    const std::vector<Order>& get_sell_queue(int item_id);

    // Returns every order made from a user.
    std::vector<Order> get_user_orders(int user_id) const;

    // Add an Order to buy or sell queue.
    // If the Order can be fulfilled, returns corresponding Contract.
    // The one with the maximum buy-price (minumum sell-price) has highest priority.
    // Any remaining quantity will be registered again as a new order.
    std::optional<Contract> register_order(const Order& order);

    // Remove every orders from queues.
    // Used to reset the market for a new day.
    void clear_orders();

private:
    // Create a contract and register the unfulfilled quantity as a new Order.
    Contract establish_contract(const Order& buy_order, const Order& sell_order);

    // Waitlist of Orders for each item.
    std::map<int, OrderQueue> m_buy_queue;
    std::map<int, OrderQueue> m_sell_queue;
};

} // namespace tradungeon

#endif
