#include "Inventory.h"
#include <exception>
#include <numeric>

namespace tradungeon
{

void Inventory::addItem(std::shared_ptr<Item> item, int quantity)
{
    if (m_slots.find(item->id()) == m_slots.end())
    {
        m_slots.insert({item->id(), InventorySlot{item, quantity}});
    }
    else
    {
        m_slots[item->id()].m_quantity += quantity;
    }
}

void Inventory::removeItem(Item* item, int quantity)
{
    if (m_slots.find(item->id()) == m_slots.end())
    {
        throw std::exception("The item doesn't exist in the inventory");
    }

    auto& slot = m_slots[item->id()];
    if (slot.m_quantity < quantity)
    {
        throw std::exception("The quantity to remove was greater than current item quantity");
    }
    else if (slot.m_quantity == quantity)
    {
        m_slots.erase(item->id());
    }
    else
    {
        slot.m_quantity -= quantity;
    }
}

const std::map<int, InventorySlot>& Inventory::slots() const
{
    return m_slots;
}

int Inventory::netWeight() const
{
    auto sum_weight = [](int sum, const auto& pair) {
        const InventorySlot& slot = pair.second;
        return sum + slot.m_item->weight() * slot.m_quantity;
    };
    return std::accumulate(m_slots.begin(), m_slots.end(), 0, sum_weight);
}

} // namespace tradungeon
