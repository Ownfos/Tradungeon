#include "interactable/DummyItem.h"

namespace tradungeon
{

DummyItem::DummyItem(std::string name, int id, int weight)
    : m_name(name), m_id(id), m_weight(weight)
{}

int DummyItem::id() const
{
    return m_id;
}

int DummyItem::weight() const
{
    return m_weight;
}

std::string DummyItem::description() const
{
    return m_name;
}

std::vector<std::shared_ptr<Action>> DummyItem::availableActions() const
{
    return {};
}

} // namespace tradungeon
