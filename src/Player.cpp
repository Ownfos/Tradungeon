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
        const ItemBundle& bundle = dropped_item->bundle();
        EventMediator::m_on_message.signal("Looted " + bundle.description());
        tryLootItem(bundle);
    }));

    m_callback_handles.push_back(EventMediator::m_on_item_drop.addCallback([this](const ItemBundle& bundle){
        EventMediator::m_on_message.signal("Dropped " + bundle.description());
        m_inventory.removeItem(bundle);
    }));

    // Item eat handler.
    m_callback_handles.push_back(EventMediator::m_on_item_eat.addCallback([this](std::shared_ptr<EdibleItem> item){
        EventMediator::m_on_message.signal("Ate " + item->description());
        m_hunger = std::max(0, m_hunger - item->hungerRestoration()); // Make sure hunger doesn't go negative.
        m_inventory.removeItem({item, 1});
    }));

    // Item trade handler.
    m_callback_handles.push_back(EventMediator::m_on_item_try_trade.addCallback([this](const Order& order){
        // An NPC wants to sell an item to the player, so check if we have enough money.
        if (order.m_type == OrderType::Sell)
        {
            if (m_money >= order.m_price)
            {
                EventMediator::m_on_item_trade_confirm.signal(order);
            }
            else
            {
                EventMediator::m_on_message.signal("You don't have enough money");
            }
        }
        // An NPC wants to buy an item from the player, so check if we have one.
        else
        {
            if (m_inventory.itemBundleWithID(order.m_item->id()))
            {
                EventMediator::m_on_item_trade_confirm.signal(order);
            }
            else
            {
                EventMediator::m_on_message.signal("You don't have that item");
            }
        }
    }));
    m_callback_handles.push_back(EventMediator::m_on_item_trade_confirm.addCallback([this](const Order& order){
        auto item = std::dynamic_pointer_cast<Item>(order.m_item);

        // Print contract information.
        auto contract_info = std::string(order.m_type == OrderType::Sell ? "Bought " : "Sold ");
        contract_info += item->description();
        contract_info += " at ";
        contract_info += std::to_string(order.m_price);
        EventMediator::m_on_message.signal(contract_info);

        // An NPC sold an item to the player.
        if (order.m_type == OrderType::Sell)
        {
            m_money -= order.m_price;
            tryLootItem({item, 1});
        }
        // An NPC bought an item from the player.
        else
        {
            m_money += order.m_price;
            m_inventory.removeItem({item, 1});
        }
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

int Player::hunger() const
{
    return m_hunger;
}

int Player::thirst() const
{
    return m_thirst;
}

int Player::inventoryWeight() const
{
    return m_inventory.netWeight();
}

int Player::inventoryWeightLimit() const
{
    return m_inventory.weightLimit();
}

int Player::money() const
{
    return m_money;
}

void Player::move(const Point& pos)
{
    m_pos = pos;
    EventMediator::m_on_time_elapse.signal(config::time_per_move);
}

void Player::resetThirst()
{
    m_thirst = 0;
}

void Player::tryLootItem(const ItemBundle& bundle)
{
    auto spare_weight = m_inventory.spareWeight();
    auto num_lootable = spare_weight / bundle.m_item->weight();

    // First put everthing in the inventory.
    m_inventory.addItem(bundle);

    // If overweight happens, remove the excess items by invoking item drop event.
    if (bundle.m_quantity > num_lootable)
    {
        EventMediator::m_on_message.signal("Inventory is full!");
        auto excess_items = ItemBundle{bundle.m_item, bundle.m_quantity - num_lootable};
        EventMediator::m_on_item_drop.signal(excess_items);
    }
}

} // namespace tradungeon
