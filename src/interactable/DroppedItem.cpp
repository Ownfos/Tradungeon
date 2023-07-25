#include "interactable/DroppedItem.h"
#include "action/ItemLootAction.h"

namespace tradungeon
{

DroppedItem::DroppedItem(const ItemBundle& bundle)
    : m_bundle(bundle)
{}

const ItemBundle& DroppedItem::bundle() const
{
    return m_bundle;
}

std::string DroppedItem::description() const
{
    return m_bundle.description();
}

std::vector<std::shared_ptr<Action>> DroppedItem::availableActions()
{
    return { std::make_shared<ItemLootAction>(shared_from_this()) };
}

} // namespace tradungeon