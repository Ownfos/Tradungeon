#ifndef TRADUNGEON_INVENTORY_WINDOW_H
#define TRADUNGEON_INVENTORY_WINDOW_H

#include "window/Window.h"
#include "Inventory.h"
#include "ScrollView.h"

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
    ScrollView m_scroll_view;
};

} // namespace tradungeon

#endif
