#ifndef TRADUNGEON_INVENTORY_H
#define TRADUNGEON_INVENTORY_H

#include "interactable/Item.h"
#include <map>

namespace tradungeon
{

class Inventory
{
public:
    Inventory(int weight_limit);

    const std::map<int, ItemBundle>& slots() const;
    const ItemBundle& item(int slot_index) const;

    int netWeight() const;
    int weightLimit() const;
    int spareWeight() const;
    int size() const;

    void addItem(const ItemBundle& bundle);
    void removeItem(const ItemBundle& bundle);

private:
    int m_weight_limit;
    std::map<int, ItemBundle> m_items;
};

} // namespace tradungeon

#endif
