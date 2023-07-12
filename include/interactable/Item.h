#ifndef TRADUNGEON_ITEM_H
#define TRADUNGEON_ITEM_H

#include "interactable/Interactable.h"
#include "Identifiable.h"
#include <memory>

namespace tradungeon
{

class Item : public Interactable, public Identifiable
{
public:
    virtual int weight() const = 0;
};

struct ItemBundle
{
    std::shared_ptr<Item> m_item;
    int m_quantity;

    std::string description() const;
    int weight() const;
};


} // namespace tradungeon

#endif
