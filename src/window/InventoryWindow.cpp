#include "window/InventoryWindow.h"

namespace tradungeon
{

InventoryWindow::InventoryWindow(const Viewport& viewport, Inventory* inventory)
    : Window(viewport), m_inventory(inventory)
{}

bool InventoryWindow::onInput(int keycode)
{

}

void InventoryWindow::onRender(TextBuffer& console)
{
    
}


} // namespace tradungeon
