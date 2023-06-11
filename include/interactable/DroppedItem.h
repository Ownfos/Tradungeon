#ifndef TRADUNGEON_DROPPED_ITEM_H
#define TRADUNGEON_DROPPED_ITEM_H

#include "interactable/Item.h"

namespace tradungeon
{

class DroppedItem : public Interactable
{
public:
    DroppedItem(const ItemBundle& bundle);
    
    virtual std::string description() const override;
    virtual std::vector<std::shared_ptr<Action>> availableActions() const override;

private:
    ItemBundle m_bundle;
};

} // namespace tradungeon

#endif
