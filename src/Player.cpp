#include "Player.h"
#include "EventMediator.h"
#include "window/InventoryWindow.h"

namespace tradungeon
{

Player::Player(const Point& pos, int inventory_weight_limit)
    : m_pos(pos), m_inventory(inventory_weight_limit)
{
    EventMediator::m_on_player_move.addCallback([this](const Point& new_pos){
        m_pos = new_pos;
    });
    EventMediator::m_on_inventory_show.addCallback([this](){
        EventMediator::m_on_window_push.signal(std::make_shared<InventoryWindow>(Viewport{{20, 5}, {40, 15}}, &m_inventory));
    });
    EventMediator::m_on_item_loot.addCallback([this](const DroppedItem* dropped_item){
        const auto& bundle = dropped_item->bundle();

        auto spare_weight = m_inventory.spareWeight();
        auto num_lootable = spare_weight / bundle.m_item->weight();

        // First put everthing in the inventory.
        m_inventory.addItem(bundle);
        EventMediator::m_on_message.signal("Looted " + bundle.description());

        // If overweight happens, remove the excess items by invoking item drop event.
        if (bundle.m_quantity > num_lootable)
        {
            EventMediator::m_on_message.signal("Inventory is full!\nDropped excess items on the ground");
            auto excess_items = ItemBundle{bundle.m_item, bundle.m_quantity - num_lootable};
            EventMediator::m_on_item_drop.signal(excess_items);
        }
    });
    EventMediator::m_on_item_drop.addCallback([this](const ItemBundle& bundle){
        m_inventory.removeItem(bundle);
        EventMediator::m_on_message.signal("Dropped " + bundle.description());
    });
}

Point Player::position() const
{
    return m_pos;
}

} // namespace tradungeon
