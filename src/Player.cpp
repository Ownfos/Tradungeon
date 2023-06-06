#include "Player.h"
#include "EventMediator.h"

namespace tradungeon
{

Player::Player(const Point& pos)
    : m_pos(pos)
{
    EventMediator::m_on_player_move.addCallback([this](const Point& new_pos){
        m_pos = new_pos;
    });
}

Point Player::position() const
{
    return m_pos;
}

} // namespace tradungeon
