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
    static Event<const std::string&> m_on_message;

    // Move item from inventory to map.
    static Event<const ItemBundle&> m_on_item_drop;
    
    // Move item from map to inventory.
    static Event<const DroppedItem*> m_on_item_loot;

    // Use item and restore hunger guage.
    static Event<std::shared_ptr<EdibleItem>> m_on_item_eat;

    // Buy or sell an item from NPC.
    // m_on_item_try_trade gets invoked first, then Player checks if it is possible.
    // If player doesn't have enought money or item, m_on_item_trade_confirm will not be invoked.
    static Event<const Order&> m_on_item_try_trade;
    static Event<const Order&> m_on_item_trade_confirm;

    static Event<void> m_on_inventory_show;

    static Event<int> m_on_time_elapse;

    static Event<std::shared_ptr<Scene>> m_on_scene_load;
    static Event<std::shared_ptr<Window>> m_on_window_push;
    static Event<void> m_on_window_pop;

    static Event<void> m_on_game_clear;
};

} // namespace tradungeon

#endif
