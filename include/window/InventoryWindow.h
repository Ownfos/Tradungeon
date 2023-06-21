#ifndef TRADUNGEON_INVENTORY_WINDOW_H
#define TRADUNGEON_INVENTORY_WINDOW_H

#include "window/Window.h"
#include "Inventory.h"

namespace tradungeon
{

class InventoryWindow : public Window
{
public:
    InventoryWindow(const Viewport& viewport, Inventory* inventory);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;

private:
    Inventory* m_inventory;
    int m_cursor_pos = 0;
};

} // namespace tradungeon

#endif
