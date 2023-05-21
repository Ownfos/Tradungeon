#ifndef TRADUNGEON_GAME_H
#define TRADUNGEON_GAME_H

#include "UIManager.h"
#include "Console.h"
#include "MessageLogViewer.h"
#include <memory>

namespace tradungeon
{

class Game
{
public:
    static Game& getInstance();

    Console m_console;
    UIManager m_ui_manager;
    std::shared_ptr<MessageLogViewer> m_msg_log_viewer;

private:
    Game();
};

} // namespace tradungeon

#endif
