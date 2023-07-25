#ifndef TRADUNGEON_INTERACTABLE_H
#define TRADUNGEON_INTERACTABLE_H

#include "action/Action.h"
#include <vector>
#include <memory>

namespace tradungeon
{

using ActionList = std::vector<std::shared_ptr<Action>>;

class Interactable : private Polymorphic
{
public:
    virtual std::string description() const = 0;
    virtual ActionList availableActions() = 0;
};

} // namespace tradungeon

#endif
