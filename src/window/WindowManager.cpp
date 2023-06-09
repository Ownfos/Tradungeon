#include "window/WindowManager.h"

namespace tradungeon
{

void WindowManager::push(std::shared_ptr<Window> window)
{
    m_window_stack.push_back(window);
}

void WindowManager::pop()
{
    m_window_stack.pop_back();
}

void WindowManager::handleInput(int keycode)
{
    for (auto it = m_window_stack.rbegin(); it != m_window_stack.rend(); ++it)
    {
        auto window_ptr = it->get();
        auto is_handled = window_ptr->onInput(keycode);
        if (is_handled)
        {
            return;
        }
    }
}

void WindowManager::render(TextBuffer& buffer)
{
    for (auto& window : m_window_stack)
    {
        window->clear(buffer, '#', ' ');
        window->onRender(buffer);
    }
}

} // namespace tradungeon
