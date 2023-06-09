#ifndef TRADUNGEON_GAME_H
#define TRADUNGEON_GAME_H

#include "Event.h"
#include "TextBuffer.h"
#include "window/WindowManager.h"
#include "window/MessageLogWindow.h"
#include "window/MapWindow.h"
#include <memory>

namespace tradungeon
{

class Game
{
public:
    Game();

    void handleInput(int keycode);
    std::string_view render();

private:
    TextBuffer m_buffer;
    WindowManager m_window_manager;
    Map m_map;
    Player m_player;
    std::shared_ptr<MessageLogWindow> m_msg_log_window;
    std::shared_ptr<MapWindow> m_map_window;
};

} // namespace tradungeon

#endif
