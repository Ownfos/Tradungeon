#include "Game.h"
#include "EventMediator.h"
#include "interactable/DroppedItem.h"
#include "interactable/DummyItem.h"
#include "Config.h"

namespace tradungeon
{

Game::Game()
    : m_buffer({120, 25}),
    m_map(config::map_size),
    m_player(config::player_start_position, config::inventory_weight_limit),
    m_msg_log_window(std::make_shared<MessageLogWindow>(Viewport{{80, 0}, {40, 25}}, config::message_log_buffer_size)),
    m_map_window(std::make_shared<MapWindow>(Viewport{{0, 0}, {80, 25}}, &m_map, &m_player))
{
    // Regenerate map until player's initial position is a movable tile.
    while (!m_map.isMovable(config::player_start_position))
    {
        m_map.reset();
    }

    m_window_manager.push(m_msg_log_window);
    m_window_manager.push(m_map_window);

    m_msg_log_window->push("Welcome to Tradungeon!");

    // Window pop/push handlers.
    EventMediator::m_on_window_push.addCallback([&](std::shared_ptr<Window> window){
        m_window_manager.push(window);
    });
    EventMediator::m_on_window_pop.addCallback([&](){
        m_window_manager.pop();
    });

    // Item loot/drop handlers.
    EventMediator::m_on_item_loot.addCallback([this](const DroppedItem* dropped_item){
        m_map.removeInteractable(m_player.position(), dropped_item);
    });
    EventMediator::m_on_item_drop.addCallback([this](const ItemBundle& bundle){
        m_map.addInteractable(m_player.position(), std::make_shared<DroppedItem>(bundle));
    });
}

void Game::handleInput(int keycode)
{
    if (keycode == 'L')
    {
        static int next_item_id = 0;
        auto bundle = ItemBundle{std::make_shared<DummyItem>("Item #" + std::to_string(next_item_id), next_item_id, 1), 10};
        auto dropped_item = std::make_shared<DroppedItem>(bundle);
        m_map.addInteractable(m_player.position(), dropped_item);
        EventMediator::m_on_item_loot.signal(dropped_item.get());
        ++next_item_id;
    }
    m_window_manager.handleInput(keycode);
}

std::string_view Game::render()
{
    m_window_manager.render(m_buffer);

    return m_buffer.getContent();
}

} // namespace tradungeon
