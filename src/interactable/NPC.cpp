#include "interactable/NPC.h"
#include "interactable/Item.h"
#include "action/ItemTradeAction.h"
#include <exception>
#include <algorithm>

namespace tradungeon
{

NPC::NPC(int id, std::string name)
    : m_id(id), m_name(name)
{}

std::string NPC::description() const
{
    return m_name;
}

ActionList NPC::availableActions() const
{
    auto actions = ActionList{};
    for (const Order& order : remainingOrders())
    {
        actions.push_back(std::make_shared<ItemTradeAction>(order));
    }
    
    return actions;
}

int NPC::id() const
{
    return m_id;
}

const std::vector<Order>& NPC::remainingOrders() const
{
    return m_orders;
}

void NPC::pushOrder(const Order& order)
{
    m_orders.push_back(order);
}

void NPC::clearOrders()
{
    m_orders.clear();
}

void NPC::decreaseOrderQuantity(const Order& order)
{
    auto it = std::find(m_orders.begin(), m_orders.end(), order);

    if (it == m_orders.end())
    {
        throw std::exception("The order does not belong to this NPC!");
    }
    
    it->m_quantity -= 1;
    if (it->m_quantity <= 0)
    {
        m_orders.erase(it);
    }
}

} // namespace tradungeon
