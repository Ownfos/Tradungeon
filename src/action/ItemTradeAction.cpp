#include "action/ItemTradeAction.h"
#include "EventMediator.h"

namespace tradungeon
{

ItemTradeAction::ItemTradeAction(const Order& order)
    : m_order(order)
{}

void ItemTradeAction::execute()
{
    EventMediator::m_on_item_try_trade.signal(m_order);
}

std::string ItemTradeAction::description() const
{
    auto desc = std::string();

    // NPC is trying to buy or sell item from player,
    // the action gets reversed in player's perspective.
    // "sell to the player" => "buy from the NPC"
    if (m_order.m_type == OrderType::Buy)
    {
        desc += "Sell ";
    }
    else
    {
        desc += "Buy ";
    }
    desc += std::dynamic_pointer_cast<Item>(m_order.m_item)->description();
    desc += " at ";
    desc += std::to_string(m_order.m_price);
    desc += " (x";
    desc += std::to_string(m_order.m_quantity);
    desc += " left)";
    
    return desc;
}

} // namespace tradungeon
