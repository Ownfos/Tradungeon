#ifndef TRADUNGEON_ITEM_H
#define TRADUNGEON_ITEM_H

#include "interactable/Interactable.h"

namespace tradungeon
{

class Item : public Interactable
{
public:
    virtual int id() const = 0;
    virtual int weight() const = 0;
};


} // namespace tradungeon

#endif
