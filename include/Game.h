#ifndef TRADUNGEON_GAME_H
#define TRADUNGEON_GAME_H

#include "UIManager.h"
#include "Console.h"
#include <memory>

namespace tradungeon
{

class Game
{
public:
    static Game& getInstance();

    std::shared_ptr<Console> m_console;
    UIManager m_ui_manager;

private:
    Game();
};

} // namespace tradungeon

#endif
