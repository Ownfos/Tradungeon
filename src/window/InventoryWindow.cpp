#include "window/InventoryWindow.h"
#include "window/InteractionWindow.h"
#include "EventMediator.h"

namespace tradungeon
{

InventoryWindow::InventoryWindow(const Viewport& viewport, Inventory* inventory)
    : Window(viewport),
    m_inventory(inventory),
    // The content size of scroll view will be properly set at onRender,
    // so passing 0 on initialization doesn't matter.
    m_scroll_view(0, viewport.m_size.m_height - 4)
{}

bool InventoryWindow::onInput(int keycode)
{
    if (keycode == 'I')
    {
        EventMediator::m_on_window_pop.signal();
    }
    else if (keycode == 'S')
    {
        m_scroll_view.scrollDown();
    }
    else if (keycode == 'W')
    {
        m_scroll_view.scrollUp();
    }
    else if (keycode == 'E')
    {
        if (m_inventory->size() > 0)
        {
            auto item = m_inventory->item(m_scroll_view.cursorPosition()).m_item.get();
            auto view = Viewport{m_viewport.m_offset + Point{20, 3 + m_scroll_view.cursorPosition()}, {30, 7}};
            EventMediator::m_on_window_push.signal(std::make_shared<InteractionWindow>(view, item));
        }
    }
    return true;
}

void InventoryWindow::onRender(TextBuffer& console)
{
    renderString(console, "Inventory", Viewport{{15, 1}, {10, 1}});

    // # items in the inventory might have changed.
    m_scroll_view.updateContentSize(m_inventory->size());

    // This is the area where the item description will be rendered.
    auto desc_area = Viewport{{2, 3}, {m_viewport.m_size.m_width - 4, 1}};

    // Render descriptions line by line.
    for (int i = m_scroll_view.begin(); i < m_scroll_view.end(); ++i, ++desc_area.m_offset.m_y)
    {
        auto desc = m_inventory->item(i).description();
        // Add an arrow to the item under cursor.
        if (i == m_scroll_view.cursorPosition())
        {
            desc += " <==";
        }
        renderString(console, desc, desc_area);
    }
}


} // namespace tradungeon
