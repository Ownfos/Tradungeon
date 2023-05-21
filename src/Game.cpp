#include "Game.h"

namespace tradungeon
{

Game::Game()
    : m_console({80, 25}),
    m_msg_log_viewer(std::make_shared<MessageLogViewer>(Viewport{{0, 15}, {80, 10}}, 50))
{
    m_ui_manager.push(m_msg_log_viewer);
}

Game& Game::getInstance()
{
    static Game game;

    return game;
}

} // namespace tradungeon
