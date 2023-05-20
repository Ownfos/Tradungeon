#ifndef TRADUNGEON_UI_MANAGER_H
#define TRADUNGEON_UI_MANAGER_H

#include "UI.h"
#include <vector>

namespace tradungeon
{

// UIManager is a singleton class that handles
// UI stack and input event cascading.
// 
// Each UI instance in UI stack will handle input and render content
// to a unique Console instance, which represents the actual console window.
//
// Input event is passed from top to bottom.
// Any unhandled event will be passed to the UI layer right below.
class UIManager
{
public:
    UIManager(std::shared_ptr<Console> console);


    // Creates and registers an instance of T which is a subclass of UI.
    // This calls std::make_shared<T>, forwarding all the variadic parameters
    // and a std::shared_ptr<Console> instance, which is required in UI base class constructor.
    //
    // For example, 'push<SampleUI>(9, 4.2)' will execute 'std::make_shared<SampleUI>(m_console, 9, 4.2)'.
    // Note that m_console is the std::shared_ptr<Console> instance provided by this class.
    template<typename T, typename... Args, typename = std::enable_if_t<std::is_base_of_v<UI, T>>>
    void push(Args&&... args);

    // Removes the uppermost layer of UI.
    void pop();

    // Renders all existing UI to the console.
    void render();

private:
    std::shared_ptr<Console> m_console;
    std::vector<std::shared_ptr<UI>> m_ui_stack;
};

} // namespace tradungeon

#include "UIManager.hpp"

#endif
