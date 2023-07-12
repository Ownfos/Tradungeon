#ifndef TRADUNGEON_NPC_TRADE_MANAGER_H
#define TRADUNGEON_NPC_TRADE_MANAGER_H

#include "interactable/NPC.h"
#include "MarketSimulator.h"
#include "Map.h"
#include <any>

namespace tradungeon
{

// Manages creating NPCs and trading with them.
class NPCTradeManager
{
public:
    NPCTradeManager();

    void placeNPC(Map* map) const;
    void registerTradableItem(const ItemConfig& item_config);

private:
    std::vector<std::shared_ptr<Trader>> m_npcs;
    MarketSimulator m_simulator;
    
    // Auxiliary members that allow fast access by ID.
    std::map<int, std::shared_ptr<NPC>> m_npc_dict;
    std::map<int, std::shared_ptr<Item>> m_item_dict;

    std::any m_callback_handle;
};

} // namespace tradungeon

#endif
