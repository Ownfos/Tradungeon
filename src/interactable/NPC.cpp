#include "interactable/NPC.h"

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
    return {}; // TODO: implement buy/sell actions
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

} // namespace tradungeon
