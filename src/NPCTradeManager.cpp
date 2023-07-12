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
    for (auto npc : m_npcs)
    {
        m_npc_dict[npc->id()] = std::dynamic_pointer_cast<NPC>(npc);
    }

    m_callback_handle = EventMediator::m_on_item_trade.addCallback([this](const Order& order){
        // Get actual NPC and Item instances.
        
    });
}

void NPCTradeManager::registerTradableItem(const ItemConfig& item_config)
{
    m_simulator.registerTradableItem(item_config);
    m_item_dict[item_config.m_item->id()] = item_config.m_item;
}

} // namespace tradungeon
