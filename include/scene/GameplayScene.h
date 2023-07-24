#ifndef TRADUNGEON_GAMEPLAY_SCENE_H
#define TRADUNGEON_GAMEPLAY_SCENE_H

#include "scene/Scene.h"
#include "window/MessageLogWindow.h"
#include "window/MapWindow.h"
#include "window/StatusWindow.h"
#include "Clock.h"
#include "NPCTradeManager.h"
#include "PeriodicEvent.h"
#include <any>

namespace tradungeon
{

class GameplayScene : public Scene
{
public:
    GameplayScene();

    virtual void onLoad() override;

private:
    // Register tradable items and generate buy/sell orders for NPCs.
    // This should be called only once throughout the game.
    void initializeMarket();

    // Create list of craft reipces.
    // This should be called only once throughout the game.
    void initializeRecipes();

    // Create new tileset and move player to the initial position.
    void resetMap();

    Map m_map;
    Player m_player;

    Clock m_clock; // Records total playtime.

    PeriodicEvent<int> m_map_reset_event;
    PeriodicEvent<int> m_market_reset_event;

    NPCTradeManager m_trade_manager;

    std::vector<CraftRecipe> m_recipes; // Passed to MapWindow, which then uses it to create CraftRecipeWindow.

    std::shared_ptr<MessageLogWindow> m_msg_log_window;
    std::shared_ptr<MapWindow> m_map_window;
    std::shared_ptr<StatusWindow> m_status_window;

    std::vector<std::any> m_callback_handles;
};

} // namespace tradungeon

#endif
