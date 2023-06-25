#ifndef TRADUNGEON_INTERACTABLE_LIST_WINDOW_H
#define TRADUNGEON_INTERACTABLE_LIST_WINDOW_H

#include "window/Window.h"
#include "interactable/Interactable.h"
#include "ScrollView.h"

namespace tradungeon
{

using InteractableList = std::vector<std::shared_ptr<Interactable>>;

class InteractableListWindow : public Window
{
public:
    InteractableListWindow(const Viewport& viewport, const InteractableList& actions);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;

private:
    const InteractableList& m_interactables;
    ScrollView m_scroll_view;
};

} // namespace tradungeon

#endif
