#include "interactable/ExitGuideItem.h"
#include "action/ExitGuideAction.h"

namespace tradungeon
{

int ExitGuideItem::id() const
{
    return 9999;
}

int ExitGuideItem::weight() const
{
    return 1;
}

std::string ExitGuideItem::description() const
{
    return "Pathfinder's ring";
}

std::vector<std::shared_ptr<Action>> ExitGuideItem::availableActions()
{
    return { std::make_shared<ExitGuideAction>() };
}

} // namespace tradungeon
