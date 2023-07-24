#ifndef TRADUNGEON_NPC_TRADE_MANAGER_H
#define TRADUNGEON_NPC_TRADE_MANAGER_H

#include "interactable/NPC.h"
#include "MarketSimulator.h"
#include "Map.h"
#include <any>
#include <set>

namespace tradungeon
{

// Manages creating NPCs and trading with them.
class NPCTradeManager
{
public:
    NPCTradeManager();

    // Randomly place NPCs on a tile that is reachable from player's initial position
    // and return a complete set of positions that the NPCs lie on.
    std::set<Point> placeNPC(Map& map, int spawn_radius) const;

    // Forwarding functions for MarketSimulator.
    void registerTradableItem(const ItemConfig& item_config);
    void generateDailyOrders();

private:
    std::vector<std::shared_ptr<Trader>> m_npcs;
    MarketSimulator m_simulator;

    std::any m_callback_handle;
};

} // namespace tradungeon

#endif
