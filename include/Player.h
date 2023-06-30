#ifndef TRADUNGEON_PLAYER_H
#define TRADUNGEON_PLAYER_H

#include "Common.h"
#include "Inventory.h"

namespace tradungeon
{

class Player
{
public:
    Player(const Point& pos, int inventory_weight_limit);

    Point position() const;
    int hunger() const;
    int thirst() const;

private:
    Point m_pos;
    Inventory m_inventory;

    int m_hunger = 0;
    int m_thirst = 0;
};

} // namespace tradungeon

#endif
