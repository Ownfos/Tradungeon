#ifndef TRADUNGEON_EVENT_MEDIATOR_H
#define TRADUNGEON_EVENT_MEDIATOR_H

#include "Event.h"
#include "Common.h"
#include "interactable/DroppedItem.h"
#include "window/Window.h"
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
    static Event<const Point&> m_on_player_move;

    // Move item from inventory to map.
    static Event<const ItemBundle&> m_on_item_drop;
    
    // Move item from map to inventory.
    static Event<const DroppedItem*> m_on_item_loot;

    static Event<void> m_on_inventory_show;

    static Event<int> m_on_time_elapse;

    static Event<std::shared_ptr<Window>> m_on_window_push;
    static Event<void> m_on_window_pop;
};

} // namespace tradungeon

#endif
