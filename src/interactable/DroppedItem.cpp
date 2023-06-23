#include "interactable/DroppedItem.h"
#include "action/ItemLootAction.h"

namespace tradungeon
{

DroppedItem::DroppedItem(const ItemBundle& bundle)
    : m_bundle(bundle)
{}

std::string DroppedItem::description() const
{
    return m_bundle.description();
}

std::vector<std::shared_ptr<Action>> DroppedItem::availableActions() const
{
    return { std::make_shared<ItemLootAction>(m_bundle) };
}

} // namespace tradungeon