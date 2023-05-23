#ifndef TRADUNGEON_GAME_H
#define TRADUNGEON_GAME_H

#include "UIManager.h"
#include "TextBuffer.h"
#include "MessageLogViewer.h"
#include <memory>

namespace tradungeon
{

class Game
{
public:
    static Game& getInstance();

    TextBuffer m_buffer;
    UIManager m_ui_manager;
    std::shared_ptr<MessageLogViewer> m_msg_log_viewer;

private:
    Game();
};

} // namespace tradungeon

#endif
