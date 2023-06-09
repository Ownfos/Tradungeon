#ifndef TRADUNGEON_UI_MANAGER_H
#define TRADUNGEON_UI_MANAGER_H

#include "window/Window.h"
#include <vector>
#include <memory>

namespace tradungeon
{

// WindowManager handles UI stack and input event cascading.
// 
// Each Window instance in Window stack will handle input and render content
// to a unique Console instance, which represents the actual console window.
//
// Input event is passed from top to bottom.
// Any unhandled event will be passed to the Window layer right below.
class WindowManager
{
public:
    void push(std::shared_ptr<Window> window);
    void pop();

    // Cascade input through Window stack.
    void handleInput(int keycode);

    // Renders all existing Window to the buffer.
    void render(TextBuffer& buffer);

private:
    std::vector<std::shared_ptr<Window>> m_window_stack;
};

} // namespace tradungeon

#endif
