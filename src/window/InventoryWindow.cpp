#include "window/InventoryWindow.h"
#include "EventMediator.h"

namespace tradungeon
{

InventoryWindow::InventoryWindow(const Viewport& viewport, Inventory* inventory)
    : Window(viewport), m_inventory(inventory)
{}

bool InventoryWindow::onInput(int keycode)
{
    if (keycode == 'I')
    {
        EventMediator::m_on_window_pop.signal();
    }
    return true;
}

void InventoryWindow::onRender(TextBuffer& console)
{
    renderString(console, "Inventory", Viewport{{15, 1}, {10, 1}});
}


} // namespace tradungeon
