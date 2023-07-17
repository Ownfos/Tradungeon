#include "scene/GameplayScene.h"
#include "EventMediator.h"
#include "Config.h"
#include "interactable/UnusableItems.h"
#include "interactable/EdibleItems.h"

namespace tradungeon
{

GameplayScene::GameplayScene()
    : m_map(config::map_size, config::exit_min_distance, config::exit_max_distance),
    m_player(config::player_start_position, config::inventory_weight_limit),
    m_map_reset_event(config::map_reset_cycle * timeunit::day, [this]{ resetMap(); }),
    m_market_reset_event(timeunit::day, [this]{ m_trade_manager.generateDailyOrders(); }),
    m_msg_log_window(std::make_shared<MessageLogWindow>(Viewport{{80, 0}, {40, 17}}, config::message_log_buffer_size)),
    m_map_window(std::make_shared<MapWindow>(Viewport{{0, 0}, {80, 25}}, &m_map, &m_player)),
    m_status_window(std::make_shared<StatusWindow>(Viewport{{80, 16}, {40, 9}}, &m_player, &m_clock))
{
    initializeMarket();
    resetMap();

    m_msg_log_window->push("Welcome to Tradungeon!");
}

void GameplayScene::onLoad()
{
    // Activate map and message viewers.
    EventMediator::m_on_window_push.signal(m_status_window);
    EventMediator::m_on_window_push.signal(m_msg_log_window);
    EventMediator::m_on_window_push.signal(m_map_window);

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
        m_map_reset_event.advanceTime(elapsed_time);
        m_market_reset_event.advanceTime(elapsed_time);
    }));

    // Game clear handler.
    m_callback_handles.push_back(EventMediator::m_on_game_clear.addCallback([]{
        // TODO: load game clear scene.
        // EventMediator::m_on_scene_load.signal(std::make_shared<GameClearScene>(/* gameplay statistics to show on clear scene */));
        EventMediator::m_on_message.signal("You succeeded finding an exit out of this dungeon!");
    }));
}

void GameplayScene::initializeMarket()
{
    // Register tradable items to the simulator.
    {
        auto item_config = ItemConfig{};
        item_config.m_item = std::make_shared<Apple>();
        item_config.m_net_demand = 10;
        item_config.m_net_supply = 10;
        item_config.m_initial_price = 100;
        item_config.m_num_buyers = 1;
        item_config.m_num_sellers = 1;
        m_trade_manager.registerTradableItem(item_config);
    }

    {
        auto item_config = ItemConfig{};
        item_config.m_item = std::make_shared<Diamond>();
        item_config.m_net_demand = 10;
        item_config.m_net_supply = 10;
        item_config.m_initial_price = 1000;
        item_config.m_num_buyers = 1;
        item_config.m_num_sellers = 1;
        m_trade_manager.registerTradableItem(item_config);
    }

    // Prepare the orders for the first day.
    m_trade_manager.generateDailyOrders();
}

void GameplayScene::resetMap()
{
    // Create a new tileset.
    m_map.reset();
    m_trade_manager.placeNPC(m_map, config::npc_spawn_radius);

    // Teleport player to the initial position.
    // Since visibility is reset, we need to manually expand visibility near the player.
    m_player.move(config::player_start_position);
    m_map.expandVisibility(m_player.position(), config::map_visibility_radius);
}

} // namespace tradungeon
