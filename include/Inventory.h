#ifndef TRADUNGEON_INVENTORY_H
#define TRADUNGEON_INVENTORY_H

#include "interactable/Item.h"
#include <memory>
#include <map>

namespace tradungeon
{

struct InventorySlot
{
    std::shared_ptr<Item> m_item;
    int m_quantity;
};

class Inventory
{
public:
    const std::map<int, InventorySlot>& slots() const;
    int netWeight() const;

    void addItem(std::shared_ptr<Item> item, int quantity);
    void removeItem(Item* item, int quantity);

private:
    std::map<int, InventorySlot> m_slots;
};

} // namespace tradungeon

#endif
