#ifndef TRADUNGEON_DROPPED_ITEM_H
#define TRADUNGEON_DROPPED_ITEM_H

#include "interactable/Item.h"

namespace tradungeon
{

class DroppedItem : public Interactable, public std::enable_shared_from_this<DroppedItem>
{
public:
    DroppedItem(const ItemBundle& bundle);

    const ItemBundle& bundle() const;
    
    virtual std::string description() const override;
    virtual std::vector<std::shared_ptr<Action>> availableActions() override;

private:
    ItemBundle m_bundle;
};

} // namespace tradungeon

#endif
