#include "action/ItemLootAction.h"
#include "EventMediator.h"

namespace tradungeon
{

ItemLootAction::ItemLootAction(std::shared_ptr<const DroppedItem> dropped_item)
    : m_dropped_item(dropped_item)
{}

void ItemLootAction::execute()
{
    EventMediator::m_on_item_loot.signal(m_dropped_item);
}

std::string ItemLootAction::description() const
{
    return "Loot " + m_dropped_item->bundle().description();
}

} // namespace tradungeon
