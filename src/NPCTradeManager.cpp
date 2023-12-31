#include "NPCTradeManager.h"
#include "EventMediator.h"

namespace tradungeon
{

NPCTradeManager::NPCTradeManager()
    : m_npcs({
        std::make_shared<NPC>(1, "Dave"),
        std::make_shared<NPC>(2, "John Doe"),
        std::make_shared<NPC>(3, "Mary"),
        std::make_shared<NPC>(4, "Lisa"),
        std::make_shared<NPC>(5, "Arnold"),
        std::make_shared<NPC>(6, "Shaw"),
        std::make_shared<NPC>(7, "Dorothy"),
        std::make_shared<NPC>(8, "Oz"),
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

std::vector<Point> NPCTradeManager::placeNPC(Map& map, int spawn_radius) const
{
    // List of all positions where NPCs are placed at.
    std::vector<Point> npc_positions;

    // The player's initial position.
    const auto player_pos = Point{
        map.size().m_width / 2,
        map.size().m_height / 2
    };

    for (auto& npc : m_npcs)
    {
        while (true)
        {
            // Select a random displacement with size less than spawn_radius.
            auto npc_displacement = Point{
                Random::range(-spawn_radius, spawn_radius),
                Random::range(-spawn_radius, spawn_radius)
            };
            if (npc_displacement.dotProduct(npc_displacement) > spawn_radius * spawn_radius)
            {
                continue;
            }

            // Check if the point is reachable from player's initial position.
            auto npc_pos = player_pos + npc_displacement;
            if (!map.findPath(player_pos, npc_pos))
            {
                continue;
            }

            // If we found a valid position, place the NPC and move on to the next one.
            map.addInteractable(npc_pos, std::dynamic_pointer_cast<NPC>(npc));
            npc_positions.push_back(npc_pos);
            break;
        }
    }

    return npc_positions;
}

void NPCTradeManager::registerTradableItem(const ItemConfig& item_config)
{
    m_simulator.registerTradableItem(item_config);
}

void NPCTradeManager::generateDailyOrders()
{
    m_simulator.generateDailyOrders();
}

} // namespace tradungeon
