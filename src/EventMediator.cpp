#include "EventMediator.h"

namespace tradungeon
{

// Define static member variables.
Event<const std::string&> EventMediator::m_on_message;
Event<const Point&> EventMediator::m_on_player_move;

} // namespace tradungeon
