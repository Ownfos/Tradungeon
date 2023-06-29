#ifndef TRADUNGEON_INVENTORY_H
#define TRADUNGEON_INVENTORY_H

#include "interactable/Item.h"
#include <numeric>
#include <map>
#include <optional>

namespace tradungeon
{

class Inventory
{
public:
    // Note: extra parenthesis around 'std::numeric_limit<int>::max' resolves conflict between member function and macro.
    Inventory(int weight_limit = (std::numeric_limits<int>::max)());

    const ItemBundle& itemBundleAtSlot(int slot_index) const;
    std::optional<std::reference_wrapper<const ItemBundle>> itemBundleWithID(int item_id) const;

    int netWeight() const;
    int weightLimit() const;
    int spareWeight() const;
    int numSlots() const;

    void addItem(const ItemBundle& bundle);
    void removeItem(const ItemBundle& bundle);

private:
    int m_weight_limit;
    std::map<int, ItemBundle> m_items;
};

} // namespace tradungeon

#endif
