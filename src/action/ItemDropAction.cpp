#include "action/ItemDropAction.h"
#include "EventMediator.h"
#include <format>

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
    return std::format("Drop {} on the ground", m_bundle.description());
}

} // namespace tradungeon
