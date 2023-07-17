#include "action/ItemEatAction.h"
#include "EventMediator.h"

namespace tradungeon
{

ItemEatAction::ItemEatAction(std::shared_ptr<EdibleItem> item)
    : m_item(item)
{}

void ItemEatAction::execute()
{
    EventMediator::m_on_item_eat.signal(m_item);
}

std::string ItemEatAction::description() const
{
    return "Eat " + m_item->description() + " (hunger -" + std::to_string(m_item->hungerRestoration()) + ")";
}

} // namespace tradungeon
