#include "interactable/EdibleItems.h"
#include "action/ItemEatAction.h"

namespace tradungeon
{

EdibleItem::EdibleItem(std::string name, int id, int weight, int hunger_restoration)
    : m_name(name), m_id(id), m_weight(weight), m_hunger_restoration(hunger_restoration)
{}

int EdibleItem::id() const
{
    return m_id;
}

int EdibleItem::weight() const
{
    return m_weight;
}

std::string EdibleItem::description() const
{
    return m_name;
}

std::vector<std::shared_ptr<Action>> EdibleItem::availableActions() const
{
    // TODO: fix the const correctness issue...
    return {
        std::make_shared<ItemEatAction>(const_cast<EdibleItem*>(this)->shared_from_this())
    };
}

int EdibleItem::hungerRestoration() const
{
    return m_hunger_restoration;
}

Apple::Apple()
    : EdibleItem("Apple", 5, 1, 10)
{}

} // namespace tradungeon
