#ifndef TRADUNGEON_ITEM_LOOT_ACTION_H
#define TRADUNGEON_ITEM_LOOT_ACTION_H

#include "action/Action.h"
#include "interactable/DroppedItem.h"

namespace tradungeon
{

class ItemLootAction : public Action
{
public:
    ItemLootAction(std::shared_ptr<const DroppedItem> dropped_item);

    virtual void execute() override;
    virtual std::string description() const override;

private:
    std::shared_ptr<const DroppedItem> m_dropped_item;
};

} // namespace tradungeon

#endif
