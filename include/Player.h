#ifndef TRADUNGEON_PLAYER_H
#define TRADUNGEON_PLAYER_H

#include "Common.h"

namespace tradungeon
{

class Player
{
public:
    Player(const Point& pos);

    Point position() const;

private:
    Point m_pos;
};

} // namespace tradungeon

#endif
