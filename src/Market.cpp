#include "Market.h"
#include <algorithm>
#include <iterator>

namespace tradungeon
{

bool Order::operator==(const Order& other) const
{
    return (m_user->id() == other.m_user->id()) && (m_item->id() == other.m_item->id());
}

const std::vector<Order>& OrderQueue::get_queue() const
{
    return m_queue;
}

void OrderQueue::push(Order order)
{
    // Make sure all elements are of same OrderType.
    if (!is_empty() && order.m_type != m_queue.front().m_type)
    {
        throw std::exception("An Order with different OrderType was pushed to the OrderQueue");
    }

    // Insertion sort
    m_queue.push_back(order);
    for (int i = m_queue.size() - 1; i > 0; --i)
    {
        if (!is_sorted(m_queue[i-1], m_queue[i]))
        {
            std::swap(m_queue[i-1], m_queue[i]);
        }
    }
}

Order OrderQueue::pop()
{
    auto ret = top();
    m_queue.pop_back();

    return ret;
}

const Order& OrderQueue::top() const
{
    return m_queue.back();
}

std::vector<Order>::const_iterator OrderQueue::begin() const
{
    return m_queue.cbegin();
}

std::vector<Order>::const_iterator OrderQueue::end() const
{
    return m_queue.cend();
}

size_t OrderQueue::size() const
{
    return m_queue.size();
}

Order OrderQueue::operator[](int index) const
{
    return m_queue[index];
}

bool OrderQueue::is_sorted(const Order& lhs, const Order& rhs)
{
    // The first element of the queue should come at the back.
    // Note that buy orders should be sorted in ascending order,
    // while sell orders should be sorted in descending order.
    switch(lhs.m_type)
    {
    case OrderType::Buy:
        return lhs.m_price <= rhs.m_price;

    case OrderType::Sell:
        return lhs.m_price >= rhs.m_price;
    }
}

bool OrderQueue::is_empty() const
{
    return m_queue.empty();
}

bool OrderQueue::is_contract_possible(const Order& order) const
{
    // There are no available orders.
    if (is_empty())
    {
        return false;
    }

    // Contract is possible only between buy and sell orders.
    if (order.m_type == top().m_type)
    {
        throw std::exception("An Order with same OrderType was given to the OrderQueue to check contract possibility");
    }

    switch(order.m_type)
    {
    case OrderType::Buy:
        return top().m_price <= order.m_price;

    case OrderType::Sell:
        return top().m_price >= order.m_price;
    }
}

const std::vector<Order>& Market::get_buy_queue(int item_id)
{
    return m_buy_queue[item_id].get_queue();
}

const std::vector<Order>& Market::get_sell_queue(int item_id)
{
    return m_sell_queue[item_id].get_queue();
}

std::optional<Contract> Market::register_order(const Order& order)
{
    const auto item_id = order.m_item->id(); // Alias for a frequently used value.

    switch (order.m_type)
    {
    case OrderType::Buy:
        if (auto& waitlist = m_sell_queue[item_id]; waitlist.is_contract_possible(order))
        {
            return establish_contract(order, waitlist.pop());
        }

        m_buy_queue[item_id].push(order);
        break;

    case OrderType::Sell:
        if (auto& waitlist = m_buy_queue[item_id]; waitlist.is_contract_possible(order))
        {
            return establish_contract(waitlist.pop(), order);
        }
        
        m_sell_queue[item_id].push(order);
        break;
    }

    return {}; // No successful contract was made.
}

Contract Market::establish_contract(const Order& buy_order, const Order& sell_order)
{
    // If the quantity matches, just return the orders.
    if (buy_order.m_quantity == sell_order.m_quantity)
    {
        return {buy_order, sell_order};
    }
    // If not, the order with higher quantity becomes a 'remaining order'
    // which should be reinserted to the queue.
    else
    {
        // Find the one with higher quantity.
        auto accomplished_order = buy_order;
        auto remaning_order = sell_order;

        if (buy_order.m_quantity > sell_order.m_quantity)
        {
            std::swap(accomplished_order, remaning_order);
        }

        // Subtract quantity accomplished by this contract
        remaning_order.m_quantity -= accomplished_order.m_quantity;

        // Reinsert the remainder to the market
        register_order(remaning_order);

        // Adjust the quantity for buy and sell order of this contract
        auto accomplished_buy_order = buy_order;
        auto accomplished_sell_order = sell_order;
        accomplished_buy_order.m_quantity = accomplished_sell_order.m_quantity = accomplished_order.m_quantity;

        return {accomplished_buy_order, accomplished_sell_order};
    }
}

void Market::clear_orders()
{
    m_buy_queue.clear();
    m_sell_queue.clear();
}

} // namespace tradungeon
