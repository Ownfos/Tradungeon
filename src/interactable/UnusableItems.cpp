#include "interactable/UnusableItems.h"

namespace tradungeon
{

UnusableItem::UnusableItem(std::string name, int id, int weight)
    : m_name(name), m_id(id), m_weight(weight)
{}

int UnusableItem::id() const
{
    return m_id;
}

int UnusableItem::weight() const
{
    return m_weight;
}

std::string UnusableItem::description() const
{
    return m_name;
}

std::vector<std::shared_ptr<Action>> UnusableItem::availableActions() const
{
    return {};
}

WoodStick::WoodStick()
    : UnusableItem("Wood stick", 0, 1)
{}

IronOre::IronOre()
    : UnusableItem("Iron ore", 1, 7)
{}

SilverOre::SilverOre()
    : UnusableItem("Silver ore", 2, 10)
{}

GoldOre::GoldOre()
    : UnusableItem("Gold ore", 3, 19)
{}

Diamond::Diamond()
    : UnusableItem("Diamond", 4, 3)
{}

Coal::Coal()
    : UnusableItem("Coal", 5, 2)
{}

IronBar::IronBar()
    : UnusableItem("Iron bar", 100, 7)
{}

SilverBar::SilverBar()
    : UnusableItem("Silver bar", 101, 10)
{}

GoldBar::GoldBar()
    : UnusableItem("Gold bar", 102, 19)
{}

} // namespace tradungeon
