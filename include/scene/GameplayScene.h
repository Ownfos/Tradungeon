#ifndef TRADUNGEON_GAMEPLAY_SCENE_H
#define TRADUNGEON_GAMEPLAY_SCENE_H

#include "scene/Scene.h"
#include "window/MessageLogWindow.h"
#include "window/MapWindow.h"
#include "window/PlayerStatusWindow.h"
#include "Clock.h"
#include "NPCTradeManager.h"
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
    // This should be called only once throughout the game!
    void initializeMarket();

    // Create new tileset and move player to the initial position.
    void resetMap();

    Map m_map;
    Player m_player;
    Clock m_map_reset_clock;
    Clock m_market_reset_clock;
    NPCTradeManager m_trade_manager;
    std::shared_ptr<MessageLogWindow> m_msg_log_window;
    std::shared_ptr<MapWindow> m_map_window;
    std::shared_ptr<PlayerStatusWindow> m_status_window;

    std::vector<std::any> m_callback_handles;
};

} // namespace tradungeon

#endif
