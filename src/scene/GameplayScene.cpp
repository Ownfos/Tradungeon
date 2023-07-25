#include "scene/GameplayScene.h"
#include "scene/GameoverScene.h"
#include "window/GeneratingMapWindow.h"
#include "EventMediator.h"
#include "Config.h"
#include "interactable/UnusableItems.h"
#include "interactable/EdibleItems.h"
#include "interactable/ExitGuideItem.h"
#include <thread>

namespace tradungeon
{

GameplayScene::GameplayScene()
    : m_map(config::map_size, config::exit_min_distance, config::exit_max_distance),
    m_player(config::player_start_position, config::inventory_weight_limit),
    m_map_reset_event(config::map_reset_cycle * timeunit::day, [this]{ resetMap(); }),
    m_market_reset_event(timeunit::day, [this]{ m_trade_manager.generateDailyOrders(); }),
    m_statistics(std::make_unique<Statistics>()),
    m_msg_log_window(std::make_shared<MessageLogWindow>(Viewport{{80, 0}, {40, 17}}, config::message_log_buffer_size)),
    m_map_window(std::make_shared<MapWindow>(Viewport{{0, 0}, {80, 25}}, m_map, m_player, m_recipes)),
    m_status_window(std::make_shared<StatusWindow>(Viewport{{80, 16}, {40, 9}}, m_player, m_clock))
{}

void GameplayScene::onLoad()
{
    // Activate map and message viewers.
    EventMediator::m_on_window_push.signal(m_status_window);
    EventMediator::m_on_window_push.signal(m_msg_log_window);
    EventMediator::m_on_window_push.signal(m_map_window);

    // Item loot/drop handlers.
    m_callback_handles.push_back(EventMediator::m_on_item_loot.addCallback([this](std::shared_ptr<const DroppedItem> dropped_item){
        m_map.removeInteractable(m_player.position(), dropped_item.get());
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

    // Exit guide item handler.
    m_callback_handles.push_back(EventMediator::m_on_exit_guide.addCallback([this]{
        auto path = m_map.findPath(m_player.position(), m_map.exitPosition()).value();
        EventMediator::m_on_message.signal(std::format("You heard a mysterious voice:\n\"{} steps...\"\n", path.size()));
    }));

    // Game clear handler.
    m_callback_handles.push_back(EventMediator::m_on_game_clear.addCallback([this]{
        EventMediator::m_on_scene_load.signal(std::make_shared<GameoverScene>(std::move(m_statistics), "You succeeded finding an exit out of this dungeon!"));
    }));
    m_callback_handles.push_back(EventMediator::m_on_player_death.addCallback([this](const std::string& reason){
        EventMediator::m_on_scene_load.signal(std::make_shared<GameoverScene>(std::move(m_statistics), reason));
    }));

    // Initialize world.
    initializeRecipes();
    initializeMarket();
    resetMap();

    m_player.tryLootItem(ItemBundle{std::make_shared<ExitGuideItem>(), 2});
}

void GameplayScene::initializeMarket()
{
    // Register tradable items to the simulator.
    {
        auto item_config = ItemConfig{};
        item_config.m_item = std::make_shared<Apple>();
        item_config.m_net_demand = 15;
        item_config.m_net_supply = 10;
        item_config.m_initial_price = 1000;
        item_config.m_num_buyers = 3;
        item_config.m_num_sellers = 2;
        m_trade_manager.registerTradableItem(item_config);
    }

    {
        auto item_config = ItemConfig{};
        item_config.m_item = std::make_shared<IronOre>();
        item_config.m_net_demand = 10;
        item_config.m_net_supply = 10;
        item_config.m_initial_price = 100;
        item_config.m_num_buyers = 2;
        item_config.m_num_sellers = 3;
        m_trade_manager.registerTradableItem(item_config);
    }

    {
        auto item_config = ItemConfig{};
        item_config.m_item = std::make_shared<IronBar>();
        item_config.m_net_demand = 5;
        item_config.m_net_supply = 5;
        item_config.m_initial_price = 200;
        item_config.m_num_buyers = 2;
        item_config.m_num_sellers = 2;
        m_trade_manager.registerTradableItem(item_config);
    }

    {
        auto item_config = ItemConfig{};
        item_config.m_item = std::make_shared<SilverOre>();
        item_config.m_net_demand = 6;
        item_config.m_net_supply = 6;
        item_config.m_initial_price = 150;
        item_config.m_num_buyers = 2;
        item_config.m_num_sellers = 2;
        m_trade_manager.registerTradableItem(item_config);
    }

    {
        auto item_config = ItemConfig{};
        item_config.m_item = std::make_shared<SilverBar>();
        item_config.m_net_demand = 3;
        item_config.m_net_supply = 3;
        item_config.m_initial_price = 300;
        item_config.m_num_buyers = 2;
        item_config.m_num_sellers = 1;
        m_trade_manager.registerTradableItem(item_config);
    }

    {
        auto item_config = ItemConfig{};
        item_config.m_item = std::make_shared<ClamSkewer>();
        item_config.m_net_demand = 5;
        item_config.m_net_supply = 3;
        item_config.m_initial_price = 1500;
        item_config.m_num_buyers = 3;
        item_config.m_num_sellers = 1;
        m_trade_manager.registerTradableItem(item_config);
    }

    {
        auto item_config = ItemConfig{};
        item_config.m_item = std::make_shared<GoldenApple>();
        item_config.m_net_demand = 5;
        item_config.m_net_supply = 3;
        item_config.m_initial_price = 3000;
        item_config.m_num_buyers = 3;
        item_config.m_num_sellers = 1;
        m_trade_manager.registerTradableItem(item_config);
    }

    {
        auto item_config = ItemConfig{};
        item_config.m_item = std::make_shared<Diamond>();
        item_config.m_net_demand = 4;
        item_config.m_net_supply = 4;
        item_config.m_initial_price = 4000;
        item_config.m_num_buyers = 1;
        item_config.m_num_sellers = 1;
        m_trade_manager.registerTradableItem(item_config);
    }

    // Prepare the orders for the first day.
    m_trade_manager.generateDailyOrders();
}

void GameplayScene::initializeRecipes()
{
    {
        auto recipe = CraftRecipe{};
        recipe.m_ingredients = {{std::make_shared<IronBar>(), 2}, {std::make_shared<SilverBar>(), 1}, {std::make_shared<WoodStick>(), 1}};
        recipe.m_product = {std::make_shared<ExitGuideItem>(), 1};
        m_recipes.push_back(recipe);
    }

    {
        auto recipe = CraftRecipe{};
        recipe.m_ingredients = {{std::make_shared<IronOre>(), 1}, {std::make_shared<Coal>(), 1}};
        recipe.m_product = {std::make_shared<IronBar>(), 1};
        m_recipes.push_back(recipe);
    }

    {
        auto recipe = CraftRecipe{};
        recipe.m_ingredients = {{std::make_shared<SilverOre>(), 1}, {std::make_shared<Coal>(), 1}};
        recipe.m_product = {std::make_shared<SilverBar>(), 1};
        m_recipes.push_back(recipe);
    }
    
    {
        auto recipe = CraftRecipe{};
        recipe.m_ingredients = {{std::make_shared<GoldOre>(), 1}, {std::make_shared<Coal>(), 1}};
        recipe.m_product = {std::make_shared<GoldBar>(), 1};
        m_recipes.push_back(recipe);
    }

    {
        auto recipe = CraftRecipe{};
        recipe.m_ingredients = {{std::make_shared<Apple>(), 1}, {std::make_shared<GoldBar>(), 1}};
        recipe.m_product = {std::make_shared<GoldenApple>(), 1};
        m_recipes.push_back(recipe);
    }

    {
        auto recipe = CraftRecipe{};
        recipe.m_ingredients = {{std::make_shared<Clam>(), 1}, {std::make_shared<WoodStick>(), 1}, {std::make_shared<Coal>(), 1}};
        recipe.m_product = {std::make_shared<ClamSkewer>(), 1};
        m_recipes.push_back(recipe);
    }
}

void GameplayScene::resetMap()
{
    // Pop-up notice to let the user know it will take some time.
    EventMediator::m_on_window_push.signal(std::make_shared<GeneratingMapWindow>());
    EventMediator::m_on_message.signal("The terrain is transforming...!");

    std::thread([this]{
        // Create a new tileset.
        m_map.reset();

        // Place NPCs and notify the positions to the map viewer.
        auto npc_positions = m_trade_manager.placeNPC(m_map, config::npc_spawn_radius);
        m_map_window->updateNPCPositions(npc_positions);

        // Teleport player to the initial position.
        // Since visibility is reset, we need to manually expand visibility near the player.
        m_player.move(config::player_start_position);
        m_map.expandVisibility(m_player.position(), config::map_visibility_radius);

        // Remove the notice.
        EventMediator::m_on_window_pop.signal();
    }).detach();
}

} // namespace tradungeon
