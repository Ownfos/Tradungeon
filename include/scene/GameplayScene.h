#ifndef TRADUNGEON_GAMEPLAY_SCENE_H
#define TRADUNGEON_GAMEPLAY_SCENE_H

#include "scene/Scene.h"
#include "window/MessageLogWindow.h"
#include "window/MapWindow.h"
#include "Clock.h"
#include <any>

namespace tradungeon
{

class GameplayScene : public Scene
{
public:
    GameplayScene();

    void onLoad() override;

private:
    Map m_map;
    Player m_player;
    Clock m_clock;
    std::shared_ptr<MessageLogWindow> m_msg_log_window;
    std::shared_ptr<MapWindow> m_map_window;

    std::vector<std::any> m_callback_handles;
};

} // namespace tradungeon

#endif
