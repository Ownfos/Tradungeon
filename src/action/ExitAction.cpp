#include "action/ExitAction.h"
#include "EventMediator.h"

namespace tradungeon
{

void ExitAction::execute()
{
    EventMediator::m_on_game_clear.signal();
}

std::string ExitAction::description() const
{
    return "Escape from this dungeon";
}

} // namespace tradungeon
