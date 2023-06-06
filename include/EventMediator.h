#ifndef TRADUNGEON_EVENT_MEDIATOR_H
#define TRADUNGEON_EVENT_MEDIATOR_H

#include "Event.h"
#include "Common.h"
#include <string>

namespace tradungeon
{

// EventMediator is a global access point for
// all instances involved in in-game event interaction.
//
// Instead of having concrete dependency between related classes (ex. Map <-> Inventory)
// they communicate through Event instance.
//
// This implementation reduces parameter explosion problem dramatically,
// but shares the same problem with the famous singleton pattern.
struct EventMediator
{
    static Event<const std::string&> m_on_message;
    static Event<const Point&> m_on_player_move;
};

} // namespace tradungeon

#endif
