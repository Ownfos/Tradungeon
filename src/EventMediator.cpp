#include "EventMediator.h"

namespace tradungeon
{

// Define static member variables.
Event<const std::string&> EventMediator::m_on_message;
Event<const ItemBundle&> EventMediator::m_on_item_drop;
Event<const DroppedItem*> EventMediator::m_on_item_loot;
Event<const Order&> EventMediator::m_on_item_trade;
Event<void> EventMediator::m_on_inventory_show;
Event<int> EventMediator::m_on_time_elapse;
Event<std::shared_ptr<Scene>> EventMediator::m_on_scene_load;
Event<std::shared_ptr<Window>> EventMediator::m_on_window_push;
Event<void> EventMediator::m_on_window_pop;
Event<void> EventMediator::m_on_game_clear;

} // namespace tradungeon
