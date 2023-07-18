#include "action/ItemEatAction.h"
#include "EventMediator.h"
#include <format>

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
    return std::format("Eat {} (hunger -{})", m_item->description(), m_item->hungerRestoration());
}

} // namespace tradungeon
