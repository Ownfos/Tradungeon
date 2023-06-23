#ifndef TRADUNGEON_DUMMY_ITEM_H
#define TRADUNGEON_DUMMY_ITEM_H

#include "interactable/Item.h"

namespace tradungeon
{

class DummyItem : public Item
{
public:
    DummyItem(std::string name, int id, int weight);

    virtual int id() const override;
    virtual int weight() const override;
    virtual std::string description() const override;
    virtual std::vector<std::shared_ptr<Action>> availableActions() const override;

private:
    std::string m_name;
    int m_id;
    int m_weight;
};

} // namespace tradungeon

#endif
