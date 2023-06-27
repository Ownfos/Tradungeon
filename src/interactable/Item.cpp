#include "interactable/Item.h"

namespace tradungeon
{

std::string ItemBundle::description() const
{
    return m_item->description() + " (x" + std::to_string(m_quantity) + ")";
}

int ItemBundle::weight() const
{
    return m_item->weight() * m_quantity;
}

} // namespace tradungeon