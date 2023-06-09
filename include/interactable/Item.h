#ifndef TRADUNGEON_ITEM_H
#define TRADUNGEON_ITEM_H

#include "interactable/Interactable.h"

namespace tradungeon
{

class Item : public Interactable
{
public:
    virtual std::string name() = 0;
    virtual int quantity() = 0;
    virtual int unit_weight() = 0;
};


} // namespace tradungeon

#endif
