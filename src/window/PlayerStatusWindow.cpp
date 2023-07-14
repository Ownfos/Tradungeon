#include "window/PlayerStatusWindow.h"
#include "Config.h"

namespace tradungeon
{

PlayerStatusWindow::PlayerStatusWindow(const Viewport& viewport, Player* player)
    : Window(viewport), m_player(player)
{}

bool PlayerStatusWindow::onInput(int keycode)
{
    return false;
}

void PlayerStatusWindow::onRender(TextBuffer& buffer)
{
    renderString(buffer, "Hunger: " + std::to_string(m_player->hunger()) + " / " + std::to_string(config::hunger_threshold), Viewport{{2, 2}, {m_viewport.m_size.m_width - 4, 1}});
    renderString(buffer, "Thirst: " + std::to_string(m_player->thirst()) + " / " + std::to_string(config::thirst_threshold), Viewport{{2, 3}, {m_viewport.m_size.m_width - 4, 1}});
    renderString(buffer, "Money: " + std::to_string(m_player->money()), Viewport{{2, 4}, {m_viewport.m_size.m_width - 4, 1}});
}

} // namespace tradungeon
