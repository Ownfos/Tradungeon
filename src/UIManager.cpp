#include "UIManager.h"

namespace tradungeon
{

void UIManager::push(std::shared_ptr<UI> ui)
{
    m_ui_stack.push_back(ui);
}

void UIManager::pop()
{
    m_ui_stack.pop_back();
}

void UIManager::handleInput(int keycode)
{
    for (auto it = m_ui_stack.rbegin(); it != m_ui_stack.rend(); ++it)
    {
        auto ui_ptr = it->get();
        auto is_handled = ui_ptr->onInput(keycode);
        if (is_handled)
        {
            return;
        }
    }
}

void UIManager::render(TextBuffer& console)
{
    for (auto& ui : m_ui_stack)
    {
        ui->clear(console, '#', ' ');
        ui->onRender(console);
    }
}

} // namespace tradungeon
