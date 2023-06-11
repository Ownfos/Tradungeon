#include "Inventory.h"
#include <exception>
#include <numeric>

namespace tradungeon
{

void Inventory::addItem(const ItemBundle& bundle)
{
    const auto id = bundle.m_item->id();
    if (m_items.find(id) == m_items.end())
    {
        m_items.insert({id, bundle});
    }
    else
    {
        m_items[id].m_quantity += bundle.m_quantity;
    }
}

void Inventory::removeItem(const ItemBundle& bundle)
{
    const auto id = bundle.m_item->id();
    if (m_items.find(id) == m_items.end())
    {
        throw std::exception("The item doesn't exist in the inventory");
    }

    const auto remainder = (m_items[id].m_quantity -= bundle.m_quantity);
    if (remainder < 0)
    {
        throw std::exception("The quantity to remove was greater than current item quantity");
    }
    else if (remainder == 0)
    {
        m_items.erase(id);
    }
}

const std::map<int, ItemBundle>& Inventory::slots() const
{
    return m_items;
}

int Inventory::netWeight() const
{
    auto sum_weight = [](int sum, const auto& pair) {
        const ItemBundle& slot = pair.second;
        return sum + slot.m_item->weight() * slot.m_quantity;
    };
    return std::accumulate(m_items.begin(), m_items.end(), 0, sum_weight);
}

} // namespace tradungeon
