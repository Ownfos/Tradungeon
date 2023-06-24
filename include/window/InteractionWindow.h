#ifndef TRADUNGEON_INTERACTION_WINDOW_H
#define TRADUNGEON_INTERACTION_WINDOW_H

#include "window/Window.h"
#include "interactable/Interactable.h"
#include "ScrollView.h"

namespace tradungeon
{

class InteractionWindow : public Window
{
public:
    InteractionWindow(const Viewport& viewport, Interactable* interactable);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;

private:
    Interactable* m_interactable;
    ScrollView m_scroll_view;
};

} // namespace tradungeon

#endif
