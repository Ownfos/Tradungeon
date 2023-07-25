#include "interactable/Exit.h"
#include "action/ExitAction.h"

namespace tradungeon
{

std::string Exit::description() const
{
    return "THE EXIT";
}

std::vector<std::shared_ptr<Action>> Exit::availableActions()
{
    return { std::make_shared<ExitAction>() };
}

} // namespace tradungeon