#include "interactable/Item.h"
#include <format>

namespace tradungeon
{

std::string ItemBundle::description() const
{
    return std::format("{} x{} [{}/ea]", m_item->description(), m_quantity, m_item->weight());
}

int ItemBundle::weight() const
{
    return m_item->weight() * m_quantity;
}

} // namespace tradungeon