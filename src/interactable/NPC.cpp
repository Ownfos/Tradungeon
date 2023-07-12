#include "interactable/NPC.h"
#include "interactable/Item.h"
#include "action/DummyAction.h"

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
    // TODO: implement buy/sell actions
    auto actions = ActionList{};
    for (const Order& order : remainingOrders())
    {
        auto item = std::dynamic_pointer_cast<Item>(order.m_item);
        
        auto desc = std::string();
        desc += (order.m_type == OrderType::Buy ? "Buy " : "Sell ");
        desc += item->description();
        desc += " for ";
        desc += std::to_string(order.m_price);
        desc += "G";

        actions.push_back(std::make_shared<DummyAction>(std::move(desc)));
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

} // namespace tradungeon
