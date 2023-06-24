#ifndef TRADUNGEON_DUMMY_ACTION_H
#define TRADUNGEON_DUMMY_ACTION_H

#include "action/Action.h"

namespace tradungeon
{

class DummyAction : public Action
{
public:
    DummyAction(std::string&& description);

    virtual void execute() override;
    virtual std::string description() const override;

private:
    std::string m_description;
};

} // namespace tradungeon

#endif
