#ifndef TRADUNGEON_PLAYER_H
#define TRADUNGEON_PLAYER_H

#include "Common.h"
#include "Inventory.h"

namespace tradungeon
{

class Player
{
public:
    Player(const Point& pos);

    Point position() const;

private:
    Point m_pos;
    Inventory m_inventory;
};

} // namespace tradungeon

#endif
