#include "window/InteractableListWindow.h"
#include "window/ActionListWindow.h"
#include "EventMediator.h"

namespace tradungeon
{

InteractableListWindow::InteractableListWindow(const Viewport& viewport, const InteractableList& interactables)
    : Window(viewport),
    m_interactables(interactables),
    m_scroll_view(interactables.size(), viewport.m_size.m_height - 4)
{}

bool InteractableListWindow::onInput(int keycode)
{
    if (keycode == 'Q')
    {
        EventMediator::m_on_window_pop.signal();
    }
    else if (keycode == 'E')
    {
        if (m_interactables.size() > 0)
        {
            // Show available actions of selected interactable on a child window.
            auto actions = m_interactables[m_scroll_view.cursorPosition()]->availableActions();
            auto viewport = Viewport{m_viewport.m_offset + Point{20, 3 + m_scroll_view.cursorPosition()}, {40, 7}};
            EventMediator::m_on_window_push.signal(std::make_shared<ActionListWindow>(viewport, actions));
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

void InteractableListWindow::onRender(TextBuffer& console)
{
    renderString(console, "Interactables", Viewport{{0, 1}, {m_viewport.m_size.m_width, 1}}, TextAlign::Center);

    // # items in the interactable list might have changed.
    m_scroll_view.updateContentSize(m_interactables.size());

    // This is the area where the action description will be rendered.
    auto desc_area = Viewport{{2, 3}, {m_viewport.m_size.m_width - 4, 1}};

    // Render descriptions line by line.
    for (int i = m_scroll_view.begin(); i < m_scroll_view.end(); ++i, ++desc_area.m_offset.m_y)
    {
        auto desc = m_interactables[i]->description();
        // Add an arrow to the action under cursor.
        if (i == m_scroll_view.cursorPosition())
        {
            desc += " <==";
        }
        renderString(console, desc, desc_area);
    }
}


} // namespace tradungeon
