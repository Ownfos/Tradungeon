#include "NPCTradeManager.h"
#include "EventMediator.h"

namespace tradungeon
{

NPCTradeManager::NPCTradeManager()
    : m_npcs({
        std::make_shared<NPC>(1, "NPC#1"),
        std::make_shared<NPC>(2, "NPC#2")
    }),
    m_simulator(m_npcs)
{
    m_callback_handle = EventMediator::m_on_item_trade_confirm.addCallback([this](const Order& order){
        // Get actual NPC and Item instances.
        auto npc = std::dynamic_pointer_cast<NPC>(order.m_user);
        auto item = std::dynamic_pointer_cast<Item>(order.m_item);

        npc->decreaseOrderQuantity(order);
    });
}

void NPCTradeManager::placeNPC(Map& map) const
{
    for (auto& npc : m_npcs)
    {
        // TODO: implement random positioning
        map.addInteractable({50, 50}, std::dynamic_pointer_cast<NPC>(npc));
    }
}

void NPCTradeManager::registerTradableItem(const ItemConfig& item_config)
{
    m_simulator.registerTradableItem(item_config);
    m_item_dict[item_config.m_item->id()] = item_config.m_item;
}

void NPCTradeManager::generateDailyOrders()
{
    m_simulator.generateDailyOrders();
}

} // namespace tradungeon
