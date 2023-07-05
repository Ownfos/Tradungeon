#include "window/InventoryWindow.h"
#include "window/ActionListWindow.h"
#include "action/ItemDropAction.h"
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
    if (keycode == 'Q' || keycode == 'I')
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
        if (m_inventory->numSlots() > 0)
        {
            // Get the list of available actions on this item
            // and add item drop action at the end.
            auto item_bundle = m_inventory->itemBundleAtSlot(m_scroll_view.cursorPosition());
            auto actions = item_bundle.m_item->availableActions();
            actions.push_back(std::make_shared<ItemDropAction>(item_bundle));

            // Create a child window right beside the cursor.
            auto viewport = Viewport{m_viewport.m_offset + Point{20, 3 + m_scroll_view.cursorPosition()}, {40, 7}};
            EventMediator::m_on_window_push.signal(std::make_shared<ActionListWindow>(viewport, actions));
        }
    }
    return true;
}

void InventoryWindow::onRender(TextBuffer& console)
{
    renderString(console, "Inventory", Viewport{{0, 1}, {m_viewport.m_size.m_width, 1}}, TextAlign::Center);

    // # items in the inventory might have changed.
    m_scroll_view.updateContentSize(m_inventory->numSlots());

    // This is the area where the item description will be rendered.
    auto desc_area = Viewport{{2, 3}, {m_viewport.m_size.m_width - 4, 1}};

    // Render descriptions line by line.
    for (int i = m_scroll_view.begin(); i < m_scroll_view.end(); ++i, ++desc_area.m_offset.m_y)
    {
        auto desc = m_inventory->itemBundleAtSlot(i).description();
        // Add an arrow to the item under cursor.
        if (i == m_scroll_view.cursorPosition())
        {
            desc += " <==";
        }
        renderString(console, desc, desc_area);
    }
}


} // namespace tradungeon
