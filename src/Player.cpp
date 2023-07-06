#include "Player.h"
#include "EventMediator.h"
#include "window/InventoryWindow.h"
#include "Config.h"

namespace tradungeon
{

Player::Player(const Point& pos, int inventory_weight_limit)
    : m_pos(pos), m_inventory(inventory_weight_limit)
{
    // Inventory window pop-up handler.
    m_callback_handles.push_back(EventMediator::m_on_inventory_show.addCallback([this](){
        EventMediator::m_on_window_push.signal(std::make_shared<InventoryWindow>(Viewport{{20, 5}, {40, 15}}, &m_inventory));
    }));

    // Item loot/drop handlers.
    m_callback_handles.push_back(EventMediator::m_on_item_loot.addCallback([this](const DroppedItem* dropped_item){
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
    }));

    m_callback_handles.push_back(EventMediator::m_on_item_drop.addCallback([this](const ItemBundle& bundle){
        m_inventory.removeItem(bundle);
        EventMediator::m_on_message.signal("Dropped " + bundle.description());
    }));

    // Hunger/thirst increment handler.
    m_callback_handles.push_back(EventMediator::m_on_time_elapse.addCallback([this](int elapsed_time){
        m_hunger += elapsed_time * config::hunger_per_time;
        m_thirst += elapsed_time * config::thirst_per_time;

        if (m_hunger >= config::hunger_threshold)
        {
            EventMediator::m_on_message.signal("Player died of hunger");
        }
        if (m_thirst >= config::thirst_threshold)
        {
            EventMediator::m_on_message.signal("Player died of thirst");
        }
    }));
}

Point Player::position() const
{
    return m_pos;
}

void Player::move(const Point& pos)
{
    m_pos = pos;
    EventMediator::m_on_time_elapse.signal(config::time_per_move);
}

} // namespace tradungeon
