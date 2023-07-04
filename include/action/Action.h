#ifndef TRADUNGEON_ACTION_H
#define TRADUNGEON_ACTION_H

#include "Polymorphic.h"
#include <string>

namespace tradungeon
{

class Action : private Polymorphic
{
public:
    virtual void execute() = 0;
    virtual std::string description() const = 0;
};

} // namespace tradungeon

#endif
