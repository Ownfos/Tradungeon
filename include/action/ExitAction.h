#ifndef TRADUNGEON_EXIT_ACTION_H
#define TRADUNGEON_EXIT_ACTION_H

#include "action/Action.h"

namespace tradungeon
{

class ExitAction : public Action
{
public:
    virtual void execute() override;
    virtual std::string description() const override;
};

} // namespace tradungeon

#endif
