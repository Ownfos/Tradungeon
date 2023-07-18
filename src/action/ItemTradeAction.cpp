#include "action/ItemTradeAction.h"
#include "EventMediator.h"
#include <format>

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

    // NPC is trying to buy or sell item from player,
    // the action gets reversed in player's perspective.
    // "sell to the player" => "buy from the NPC"
    auto desc = std::format("{} {} at {} (x{} left)",
        (m_order.m_type == OrderType::Buy ? "Sell" : "Buy"),
        std::dynamic_pointer_cast<Item>(m_order.m_item)->description(),
        m_order.m_price,
        m_order.m_quantity
    );
    
    return desc;
}

} // namespace tradungeon
