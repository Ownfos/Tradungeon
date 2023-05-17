#include "UIManager.h"

namespace tradungeon
{

template<typename T, typename... Args>
void UIManager::push(Args&&... args)
{
    m_ui_stack.push_back(std::make_shared<T>(m_console, std::forward<Args>(args)...));
}

} // namespace tradungeon
