#include "Game.h"

namespace tradungeon
{

Game::Game()
    : m_buffer({120, 25}),
    m_map({100, 100}),
    m_player({50, 50}),
    m_msg_log_viewer(std::make_shared<MessageLogViewer>(Viewport{{80, 0}, {40, 25}}, 50)),
    m_map_viewer(std::make_shared<MapViewer>(Viewport{{0, 0}, {80, 25}}, &m_map, &m_player))
{
    m_ui_manager.push(m_msg_log_viewer);
    m_ui_manager.push(m_map_viewer);

    m_msg_log_viewer->push("Welcome to Tradungeon!");
}

void Game::handleInput(int keycode)
{
    m_ui_manager.handleInput(keycode);
}

std::string_view Game::render()
{
    m_ui_manager.render(m_buffer);

    return m_buffer.getContent();
}

} // namespace tradungeon
