#include "action/ItemDropAction.h"
#include "EventMediator.h"

namespace tradungeon
{

ItemDropAction::ItemDropAction(const ItemBundle& bundle)
    : m_bundle(bundle)
{}

void ItemDropAction::execute()
{
    EventMediator::m_on_item_drop.signal(m_bundle);
}

std::string ItemDropAction::description() const
{
    return "Drop " + m_bundle.description() + " on the ground";
}

} // namespace tradungeon
