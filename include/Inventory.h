#ifndef TRADUNGEON_INVENTORY_H
#define TRADUNGEON_INVENTORY_H

#include "interactable/Item.h"
#include <map>

namespace tradungeon
{

class Inventory
{
public:
    const std::map<int, ItemBundle>& slots() const;
    int netWeight() const;

    void addItem(const ItemBundle& bundle);
    void removeItem(const ItemBundle& bundle);

private:
    std::map<int, ItemBundle> m_items;
};

} // namespace tradungeon

#endif
