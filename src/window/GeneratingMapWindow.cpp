#include "window/GeneratingMapWindow.h"

using namespace std::chrono_literals;

namespace tradungeon
{

GeneratingMapWindow::GeneratingMapWindow()
    : Window(Viewport{{40, 10}, {40, 5}}),
    m_flicker_timer(500ms, [this]{ m_flicker = !m_flicker; })
{}

bool GeneratingMapWindow::onInput(int keycode)
{
    // Prevent all actions.
    return true;
}

void GeneratingMapWindow::onRender(TextBuffer& buffer)
{
    if (m_flicker)
    {
        renderString(buffer, "Generating map...", Viewport{{0, 2}, m_viewport.m_size}, TextAlign::Center);
    }
}

void GeneratingMapWindow::onUpdate(std::chrono::milliseconds delta_time)
{
    m_flicker_timer.advanceTime(delta_time);
}

} // namespace tradungeon
