#include "UIManager.h"
#include <iostream>

namespace tradungeon
{

UIManager::UIManager()
    : m_console(std::make_shared<Console>(Size{80, 40}))
{
    std::cout << "UIMANAGER";
}

void UIManager::pop()
{
    m_ui_stack.pop_back();
}

void UIManager::render()
{
    for (auto& ui : m_ui_stack)
    {
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
