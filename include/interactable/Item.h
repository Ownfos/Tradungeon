#ifndef TRADUNGEON_ITEM_H
#define TRADUNGEON_ITEM_H

#include "interactable/Interactable.h"
#include <memory>

namespace tradungeon
{

class Item : public Interactable
{
public:
    virtual int id() const = 0;
    virtual int weight() const = 0;
};

struct ItemBundle
{
    std::shared_ptr<Item> m_item;
    int m_quantity;

    std::string description() const;
};


} // namespace tradungeon

#endif
