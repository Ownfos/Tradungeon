#include "window/StatusWindow.h"
#include "Config.h"

namespace tradungeon
{

StatusWindow::StatusWindow(const Viewport& viewport, Player* player, Clock* clock)
    : Window(viewport), m_player(player), m_clock(clock)
{}

bool StatusWindow::onInput(int keycode)
{
    return false;
}

void StatusWindow::onRender(TextBuffer& buffer)
{
    renderString(buffer, "Hunger: " + std::to_string(m_player->hunger()) + " / " + std::to_string(config::hunger_threshold), Viewport{{2, 2}, {m_viewport.m_size.m_width - 4, 1}}, TextAlign::Center);
    renderString(buffer, "Thirst: " + std::to_string(m_player->thirst()) + " / " + std::to_string(config::thirst_threshold), Viewport{{2, 3}, {m_viewport.m_size.m_width - 4, 1}}, TextAlign::Center);
    renderString(buffer, "Money: " + std::to_string(m_player->money()), Viewport{{2, 4}, {m_viewport.m_size.m_width - 4, 1}}, TextAlign::Center);

    auto formatted_time = std::string("Day #");
    formatted_time += std::to_string(m_clock->day() + 1); // Note: time starts at 0, so day 0 is the first day.
    formatted_time += " ";
    formatted_time += std::to_string(m_clock->hour() % 12);
    formatted_time += ":";
    formatted_time += std::to_string(m_clock->minute());
    formatted_time += " ";
    formatted_time += (m_clock->hour() < 12 ? "A.M." : "P.M.");
    renderString(buffer, formatted_time, Viewport{{2, 5}, {m_viewport.m_size.m_width - 4, 1}}, TextAlign::Center);
}

} // namespace tradungeon
