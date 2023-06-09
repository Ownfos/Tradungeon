#ifndef TRADUNGEON_ACTION_H
#define TRADUNGEON_ACTION_H

#include <string>

namespace tradungeon
{

class Action
{
public:
    Action() = default;

    // Prevent object slicing.
    Action(const Action&) = delete;
    Action(Action&&) = delete;
    Action& operator=(const Action&) = delete;
    Action& operator=(Action&&) = delete;

    virtual ~Action() = default;

    virtual void execute() = 0;
    virtual std::string description() const = 0;
};

} // namespace tradungeon

#endif
