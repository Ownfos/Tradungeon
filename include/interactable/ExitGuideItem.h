#ifndef TRADUNGEON_EXIT_GUIDE_ITEM_H
#define TRADUNGEON_EXIT_GUIDE_ITEM_H

#include "interactable/Item.h"

namespace tradungeon
{

class ExitGuideItem : public Item
{
public:
    virtual int id() const override;
    virtual int weight() const override;
    virtual std::string description() const override;
    virtual std::vector<std::shared_ptr<Action>> availableActions() const override;
};

} // namespace tradungeon

#endif
