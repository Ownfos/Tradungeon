#include "action/DummyAction.h"
#include "EventMediator.h"

namespace tradungeon
{

DummyAction::DummyAction(std::string&& description)
    : m_description(std::move(description))
{}

void DummyAction::execute()
{
    EventMediator::m_on_message.signal("executed action: " + m_description);
}

std::string DummyAction::description() const
{
    return m_description;
}

} // namespace tradungeon
