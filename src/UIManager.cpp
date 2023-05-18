#include "UIManager.h"

namespace tradungeon
{

UIManager::UIManager()
    : m_console(std::make_shared<Console>(Size{80, 25}))
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

UIManager& UIManager::getInstance()
{
    static UIManager instance;

    return instance;
}

} // namespace tradungeon
