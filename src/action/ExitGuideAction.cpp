#include "action/ExitGuideAction.h"
#include "EventMediator.h"

namespace tradungeon
{

void ExitGuideAction::execute()
{
    EventMediator::m_on_exit_guide.signal();
}

std::string ExitGuideAction::description() const
{
    return "Wear the ring";
}

} // namespace tradungeon
