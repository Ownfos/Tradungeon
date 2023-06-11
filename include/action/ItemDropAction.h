#ifndef TRADUNGEON_ITEM_DROP_ACTION_H
#define TRADUNGEON_ITEM_DROP_ACTION_H

#include "action/Action.h"
#include "interactable/Item.h"

namespace tradungeon
{

class ItemDropAction : public Action
{
public:
    ItemDropAction(const ItemBundle& bundle);

    virtual void execute() override;
    virtual std::string description() const override;

private:
    ItemBundle m_bundle;
};

} // namespace tradungeon

#endif
