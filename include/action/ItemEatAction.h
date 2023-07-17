#ifndef TRADUNGEON_ITEM_TRADE_ACTION_H
#define TRADUNGEON_ITEM_TRADE_ACTION_H

#include "action/Action.h"
#include "interactable/EdibleItems.h"

namespace tradungeon
{

class ItemEatAction : public Action
{
public:
    ItemEatAction(std::shared_ptr<EdibleItem> item);

    virtual void execute() override;
    virtual std::string description() const override;

private:
    std::shared_ptr<EdibleItem> m_item;
};

} // namespace tradungeon

#endif
