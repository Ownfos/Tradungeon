#include "Player.h"
#include "EventMediator.h"
#include "window/InventoryWindow.h"

namespace tradungeon
{

Player::Player(const Point& pos)
    : m_pos(pos)
{
    EventMediator::m_on_player_move.addCallback([this](const Point& new_pos){
        m_pos = new_pos;
    });
    EventMediator::m_on_inventory_show.addCallback([this](){
        EventMediator::m_on_window_push.signal(std::make_shared<InventoryWindow>(Viewport{{20, 5}, {40, 15}}, &m_inventory));
    });
    EventMediator::m_on_item_loot.addCallback([this](const ItemBundle& bundle){
        m_inventory.addItem(bundle);
        EventMediator::m_on_message.signal("Looted " + bundle.description());
    });
}

Point Player::position() const
{
    return m_pos;
}

} // namespace tradungeon
