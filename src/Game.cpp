#include "Game.h"

namespace tradungeon
{

Game::Game()
    : m_console(std::make_shared<Console>(Size{80, 25})),
    m_ui_manager(m_console)
{}

Game& Game::getInstance()
{
    static Game game;

    return game;
}

} // namespace tradungeon
