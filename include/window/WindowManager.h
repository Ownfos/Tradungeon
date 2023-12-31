#ifndef TRADUNGEON_WINDOW_MANAGER_H
#define TRADUNGEON_WINDOW_MANAGER_H

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
//
// On the other hand, updating and rendering is done from bottom to top
// so that the latest window can appear on the top layer.
class WindowManager
{
public:
    void push(std::shared_ptr<Window> window);
    void pop();
    void clear();

    // Cascade input through Window stack.
    void handleInput(int keycode);

    // Updates all existing Windows.
    void update(std::chrono::milliseconds delta_time);

    // Renders all existing Window to the buffer.
    void render(TextBuffer& buffer);

private:
    std::vector<std::shared_ptr<Window>> m_window_stack;
};

} // namespace tradungeon

#endif
