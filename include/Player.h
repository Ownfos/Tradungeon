#ifndef TRADUNGEON_PLAYER_H
#define TRADUNGEON_PLAYER_H

#include "Common.h"
#include "Inventory.h"
#include <any>

namespace tradungeon
{

class Player
{
public:
    Player(const Point& pos, int inventory_weight_limit);

    Point position() const;
    int hunger() const;
    int thirst() const;
    int money() const;

    void move(const Point& pos);

    // Adds item to the inventory.
    // If we reach weight limit, excess items will be dropped on the map.
    void tryLootItem(const ItemBundle& bundle);

private:
    Point m_pos;
    Inventory m_inventory;

    int m_money = 100000;
    int m_hunger = 0;
    int m_thirst = 0;

    std::vector<std::any> m_callback_handles;
};

} // namespace tradungeon

#endif
