#include "Player.h"

namespace tradungeon
{

Player::Player(const Point& pos)
    : m_pos(pos)
{}

Point Player::position() const
{
    return m_pos;
}

} // namespace tradungeon
