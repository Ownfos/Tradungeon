#ifndef TRADUNGEON_EVENT_MEDIATOR_H
#define TRADUNGEON_EVENT_MEDIATOR_H

#include "Event.h"
#include "Common.h"
#include "Market.h"
#include "interactable/DroppedItem.h"
#include "interactable/EdibleItems.h"
#include "window/Window.h"
#include "scene/Scene.h"
#include <string>
#include <memory>

namespace tradungeon
{

// EventMediator is a global access point for
// all instances involved in in-game event interaction.
//
// Instead of having concrete dependency between related classes (ex. Map <-> Inventory)
// they communicate through Event instance.
//
// This implementation reduces parameter explosion problem dramatically,
// but shares the same problem with the famous singleton pattern.
struct EventMediator
{
    static inline auto m_on_message = Event<const std::string&>();

    // Move item from inventory to map.
    static inline auto m_on_item_drop = Event<const ItemBundle&>();
    
    // Move item from map to inventory.
    static inline auto  m_on_item_loot = Event<std::shared_ptr<const DroppedItem>>();

    // Use item and restore hunger guage.
    static inline auto m_on_item_eat = Event<std::shared_ptr<EdibleItem>>();

    // Buy or sell an item from NPC.
    // m_on_item_try_trade gets invoked first, then Player checks if it is possible.
    // If player doesn't have enought money or item, m_on_item_trade_confirm will not be invoked.
    static inline auto m_on_item_try_trade =  Event<const Order&>();
    static inline auto m_on_item_trade_confirm = Event<const Order&>();

    static inline auto m_on_inventory_show = Event<void>();

    static inline auto m_on_time_elapse = Event<int>();

    static inline auto m_on_scene_load = Event<std::shared_ptr<Scene>>();
    static inline auto m_on_window_push = Event<std::shared_ptr<Window>>();
    static inline auto m_on_window_pop = Event<void>();

    static inline auto m_on_game_clear = Event<void>();
    static inline auto m_on_player_death = Event<const std::string&>();

    static inline auto m_on_exit_guide = Event<void>();

    // Used by 'Statistics'
    static inline auto m_on_player_walk = Event<void>();
    static inline auto m_on_item_craft = Event<void>();
};

} // namespace tradungeon

#endif
