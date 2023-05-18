#include "UIManager.h"

namespace tradungeon
{

template<typename T, typename... Args, typename = std::enable_if_t<std::is_base_of_v<UI, T>>>
void UIManager::push(Args&&... args)
{
    m_ui_stack.push_back(std::make_shared<T>(m_console, std::forward<Args>(args)...));
}

} // namespace tradungeon
