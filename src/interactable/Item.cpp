#include "interactable/Item.h"
#include <format>

namespace tradungeon
{

std::string ItemBundle::description() const
{
    return std::format("{} (x{})", m_item->description(), m_quantity);
}

int ItemBundle::weight() const
{
    return m_item->weight() * m_quantity;
}

} // namespace tradungeon