#ifndef TRADUNGEON_ACTION_LIST_WINDOW_H
#define TRADUNGEON_ACTION_LIST_WINDOW_H

#include "window/Window.h"
#include "interactable/Interactable.h"
#include "ScrollView.h"

namespace tradungeon
{

class ActionListWindow : public Window
{
public:
    ActionListWindow(const Viewport& viewport, const ActionList& actions);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;

private:
    ActionList m_actions;
    ScrollView m_scroll_view;
};

} // namespace tradungeon

#endif
