#include "window/InventoryWindow.h"
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
    return true;
}

void InventoryWindow::onRender(TextBuffer& console)
{
    renderString(console, "Inventory", Viewport{{15, 1}, {10, 1}});

    // # items in the inventory might have changed.
    m_scroll_view.updateContentSize(m_inventory->slots().size());

    // Get the iterator to the first item to render.
    auto item_it = m_inventory->slots().begin();
    std::advance(item_it, m_scroll_view.begin());

    // This is the area where the item description will be rendered.
    auto item_slot_view = Viewport{{2, 3}, {m_viewport.m_size.m_width - 4, 1}};

    // Render descriptions line by line.
    for (int i = m_scroll_view.begin(); i < m_scroll_view.end(); ++i, ++item_it, ++item_slot_view.m_offset.m_y)
    {
        auto desc = item_it->second.description();
        // Add an arrow to the item under cursor.
        if (i == m_scroll_view.cursorPosition())
        {
            desc += " <==";
        }
        renderString(console, desc, item_slot_view);
    }
}


} // namespace tradungeon
