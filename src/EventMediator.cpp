#include "EventMediator.h"

namespace tradungeon
{

// Define static member variables.
Event<const std::string&> EventMediator::m_on_message;
Event<const Point&> EventMediator::m_on_player_move;
Event<const ItemBundle&> EventMediator::m_on_item_drop;
Event<const DroppedItem*> EventMediator::m_on_item_loot;
Event<void> EventMediator::m_on_inventory_show;
Event<int> EventMediator::m_on_time_elapse;
Event<std::shared_ptr<Window>> EventMediator::m_on_window_push;
Event<void> EventMediator::m_on_window_pop;

} // namespace tradungeon
