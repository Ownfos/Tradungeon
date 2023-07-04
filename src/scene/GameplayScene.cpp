#include "scene/GameplayScene.h"
#include "EventMediator.h"
#include "Config.h"

namespace tradungeon
{

GameplayScene::GameplayScene()
    : m_map(config::map_size, config::exit_min_distance, config::exit_max_distance),
    m_player(config::player_start_position, config::inventory_weight_limit),
    m_msg_log_window(std::make_shared<MessageLogWindow>(Viewport{{80, 0}, {40, 25}}, config::message_log_buffer_size)),
    m_map_window(std::make_shared<MapWindow>(Viewport{{0, 0}, {80, 25}}, &m_map, &m_player))
{}

void GameplayScene::onLoad()
{
    // Regenerate map until player's initial position is a movable tile.
    while (!m_map.isMovable(config::player_start_position))
    {
        m_map.reset();
    }

    EventMediator::m_on_window_push.signal(m_msg_log_window);
    EventMediator::m_on_window_push.signal(m_map_window);

    m_msg_log_window->push("Welcome to Tradungeon!");

    // Item loot/drop handlers.
    m_callback_handles.push_back(EventMediator::m_on_item_loot.addCallback([this](const DroppedItem* dropped_item){
        m_map.removeInteractable(m_player.position(), dropped_item);
    }));
    m_callback_handles.push_back(EventMediator::m_on_item_drop.addCallback([this](const ItemBundle& bundle){
        m_map.addInteractable(m_player.position(), std::make_shared<DroppedItem>(bundle));
    }));

    // Time related events.
    m_callback_handles.push_back(EventMediator::m_on_time_elapse.addCallback([this](int elapsed_time){
        m_clock.m_time += elapsed_time;

        // Reset the map periodically.
        if (m_clock.day() >= config::map_reset_cycle)
        {
            m_map.reset();

            // Start counting days from 0.
            m_clock.m_time -= config::map_reset_cycle * timeunit::day;
        }

        // TODO: handle market orders
    }));
}

} // namespace tradungeon
