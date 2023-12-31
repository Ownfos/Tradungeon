#include "window/ActionListWindow.h"
#include "EventMediator.h"

namespace tradungeon
{

ActionListWindow::ActionListWindow(const Viewport& viewport, const ActionList& actions)
    : Window(viewport),
    m_actions(actions),
    m_scroll_view(actions.size(), viewport.m_size.m_height - 4)
{}

bool ActionListWindow::onInput(int keycode)
{
    if (keycode == 'Q')
    {
        EventMediator::m_on_window_pop.signal();
    }
    else if (keycode == 'E')
    {
        if (m_actions.size() > 0)
        {
            m_actions[m_scroll_view.cursorPosition()]->execute();
            EventMediator::m_on_window_pop.signal();
        }
    }
    else if (keycode == 'S')
    {
        m_scroll_view.scrollDown();
    }
    else if (keycode == 'W')
    {
        m_scroll_view.scrollUp();
    }
    return true;
}

void ActionListWindow::onRender(TextBuffer& console)
{
    renderString(console, "Select Action", Viewport{{0, 1}, {m_viewport.m_size.m_width, 1}}, TextAlign::Center);

    // This is the area where the action description will be rendered.
    auto desc_area = Viewport{{2, 3}, {m_viewport.m_size.m_width - 4, 1}};

    // Render descriptions line by line.
    for (int i = m_scroll_view.begin(); i < m_scroll_view.end(); ++i, ++desc_area.m_offset.m_y)
    {
        auto desc = m_actions[i]->description();
        // Add an arrow to the action under cursor.
        if (i == m_scroll_view.cursorPosition())
        {
            desc += " <==";
        }
        renderString(console, desc, desc_area);
    }
}


} // namespace tradungeon
