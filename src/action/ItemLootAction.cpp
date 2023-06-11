#include "action/ItemLootAction.h"
#include "EventMediator.h"

namespace tradungeon
{

ItemLootAction::ItemLootAction(const ItemBundle& bundle)
    : m_bundle(bundle)
{}

void ItemLootAction::execute()
{
    EventMediator::m_on_item_loot.signal(m_bundle);
}

std::string ItemLootAction::description() const
{
    return "Loot " + m_bundle.description();
}

} // namespace tradungeon
