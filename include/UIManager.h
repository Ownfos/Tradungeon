#ifndef TRADUNGEON_UI_MANAGER_H
#define TRADUNGEON_UI_MANAGER_H

#include "UI.h"
#include <vector>
#include <memory>

namespace tradungeon
{

// UIManager is a singleton class that handles
// UI stack and input event cascading.
// 
// Each UI instance in UI stack will handle input and render content
// to a unique Console instance, which represents the actual console window.
//
// Input event is passed from top to bottom.
// Any unhandled event will be passed to the UI layer right below.
class UIManager
{
public:
    void push(std::shared_ptr<UI> ui);
    void pop();

    // Cascade input through UI stack.
    void handleInput(int keycode);

    // Renders all existing UI to the buffer.
    void render(TextBuffer& buffer);

private:
    std::vector<std::shared_ptr<UI>> m_ui_stack;
};

} // namespace tradungeon

#endif
