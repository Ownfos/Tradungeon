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
    // TODO: implement and add "loot 1 ~ N item", probably using another UI.
    auto actions = std::vector<std::shared_ptr<Action>>();

    // Loot only 1 item
    if (m_bundle.m_quantity > 1)
    {
        actions.push_back(std::make_shared<ItemLootAction>(ItemBundle{m_bundle.m_item, 1}));
    }

    // Loot everyting
    actions.push_back(std::make_shared<ItemLootAction>(m_bundle));
    
    return actions;
}

} // namespace tradungeon