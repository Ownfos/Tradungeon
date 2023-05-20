#include "UIManager.h"

namespace tradungeon
{

UIManager::UIManager(std::shared_ptr<Console> console)
    : m_console(console)
{}

void UIManager::pop()
{
    m_ui_stack.pop_back();
}

void UIManager::render()
{
    for (auto& ui : m_ui_stack)
    {
        ui->clear('#', ' ');
        ui->onRender();
    }
    m_console->print();
}

} // namespace tradungeon
