#ifndef TRADUNGEON_EXIT_GUIDE_ACTION_H
#define TRADUNGEON_EXIT_GUIDE_ACTION_H

#include "action/Action.h"

namespace tradungeon
{

class ExitGuideAction : public Action
{
public:
    virtual void execute() override;
    virtual std::string description() const override;
};

} // namespace tradungeon

#endif
