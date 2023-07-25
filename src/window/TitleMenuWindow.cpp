#include "window/TitleMenuWindow.h"
#include "window/HelpWindow.h"
#include "scene/GameplayScene.h"
#include "EventMediator.h"
#include <format>

using namespace std::chrono_literals;

namespace tradungeon
{

TitleMenuWindow::TitleMenuWindow(const Viewport& viewport)
    : Window(viewport), m_flicker_text_timer(500ms, [this]{ m_flicker_text = !m_flicker_text; })
{}

bool TitleMenuWindow::onInput(int keycode)
{
    // There are only two options ('New Game' and 'Help'),
    // so moving up and down behaves the same.
    if (keycode == 'W' || keycode == 'S')
    {
        m_cursor_pos = (m_cursor_pos + 1) % 2;
    }
    else if (keycode == 'E')
    {
        if (m_cursor_pos == 0)
        {
            EventMediator::m_on_scene_load.signal(std::make_shared<GameplayScene>());
        }
        else
        {
            EventMediator::m_on_window_push.signal(std::make_shared<HelpWindow>());
        }
    }
    return true;
}

void TitleMenuWindow::onRender(TextBuffer& buffer)
{
    const auto line_area = Size{m_viewport.m_size.m_width, 1};
    renderString(buffer, "TRADUNGEON", Viewport{{0, 4}, line_area}, TextAlign::Center);

    auto menu = std::vector<std::string>{
        "New Game",
        "Help"
    };
    for (int i = 0; i < 2; ++i)
    {
        auto string_to_display = (i == m_cursor_pos ? std::format("[ {} ]", menu[i]) : menu[i]);
        renderString(buffer, string_to_display, Viewport{{0, 12 + i}, line_area}, TextAlign::Center);
    }

    if (m_flicker_text)
    {
        renderString(buffer, "- press 'E' to select a menu -", Viewport{{0, 20}, line_area}, TextAlign::Center);
        renderString(buffer, "- press 'W' or 'S' to scroll menu -", Viewport{{0, 21}, line_area}, TextAlign::Center);
    }
}

void TitleMenuWindow::onUpdate(std::chrono::milliseconds delta_time)
{
    m_flicker_text_timer.advanceTime(delta_time);
}

} // namespace tradungeon
