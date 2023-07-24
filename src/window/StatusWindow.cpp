#include "window/StatusWindow.h"
#include "Config.h"
#include <format>

namespace tradungeon
{

StatusWindow::StatusWindow(const Viewport& viewport, Player& player, Clock& clock)
    : Window(viewport), m_player(player), m_clock(clock)
{}

bool StatusWindow::onInput(int keycode)
{
    return false;
}

void StatusWindow::onRender(TextBuffer& buffer)
{
    renderString(buffer, std::format("Hunger: {} / {}", m_player.hunger(), config::hunger_threshold), Viewport{{2, 2}, {m_viewport.m_size.m_width - 4, 1}}, TextAlign::Center);
    renderString(buffer, std::format("Thirst: {} / {}", m_player.thirst(), config::thirst_threshold), Viewport{{2, 3}, {m_viewport.m_size.m_width - 4, 1}}, TextAlign::Center);
    renderString(buffer, std::format("Weight: {} / {}", m_player.inventoryWeight(), m_player.inventoryWeightLimit()), Viewport{{2, 4}, {m_viewport.m_size.m_width - 4, 1}}, TextAlign::Center);
    renderString(buffer, std::format("Money: {}", m_player.money()), Viewport{{2, 5}, {m_viewport.m_size.m_width - 4, 1}}, TextAlign::Center);

    auto formatted_time = std::format("Day #{} {}:{} {}",
        m_clock.day() + 1, // Note: time starts at 0, so day 0 is the first day.
        m_clock.hour() % 12,
        m_clock.minute(),
        (m_clock.hour() < 12 ? "A.M." : "P.M.")
    );
    renderString(buffer, formatted_time, Viewport{{2, 6}, {m_viewport.m_size.m_width - 4, 1}}, TextAlign::Center);
}

} // namespace tradungeon
