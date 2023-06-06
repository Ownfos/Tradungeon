#ifndef TRADUNGEON_GAME_H
#define TRADUNGEON_GAME_H

#include "Event.h"
#include "UIManager.h"
#include "TextBuffer.h"
#include "MessageLogViewer.h"
#include "MapViewer.h"
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
    UIManager m_ui_manager;
    Map m_map;
    Player m_player;
    std::shared_ptr<MessageLogViewer> m_msg_log_viewer;
    std::shared_ptr<MapViewer> m_map_viewer;
};

} // namespace tradungeon

#endif
