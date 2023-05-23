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

void UIManager::render(TextBuffer& console)
{
    for (auto& ui : m_ui_stack)
    {
        ui->clear(console, '#', ' ');
        ui->onRender(console);
    }
}

} // namespace tradungeon
