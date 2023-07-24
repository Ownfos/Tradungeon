#include "window/CraftRecipeListWindow.h"
#include "window/CraftRecipeWindow.h"
#include "EventMediator.h"

namespace tradungeon
{

CraftRecipeListWindow::CraftRecipeListWindow(const Viewport& viewport, const std::vector<CraftRecipe>& recipes, Player& player)
    : Window(viewport),
    m_recipes(recipes),
    m_player(player),
    m_scroll_view(recipes.size(), viewport.m_size.m_height - 4)
{}

bool CraftRecipeListWindow::onInput(int keycode)
{
    if (keycode == 'Q')
    {
        EventMediator::m_on_window_pop.signal();
    }
    else if (keycode == 'E')
    {
        if (m_recipes.size() > 0)
        {
            // Show available actions of selected interactable on a child window.
            const auto& recipe = m_recipes[m_scroll_view.cursorPosition()];
            auto viewport = Viewport{m_viewport.m_offset + Point{30, 3 + m_scroll_view.cursorPosition()}, {40, 10}};
            EventMediator::m_on_window_push.signal(std::make_shared<CraftRecipeWindow>(viewport, recipe, m_player));
        }
    }
    else if (keycode == 'S')
    {
        m_scroll_view.scrollDown();
    }
    else if (keycode == 'W')
    {
        m_scroll_view.scrollUp();
    }
    return true;
}

void CraftRecipeListWindow::onRender(TextBuffer& console)
{
    renderString(console, "Craft Recipes", Viewport{{0, 1}, {m_viewport.m_size.m_width, 1}}, TextAlign::Center);

    // This is the area where the recipe description will be rendered.
    auto desc_area = Viewport{{2, 3}, {m_viewport.m_size.m_width - 4, 1}};

    // Render descriptions line by line.
    for (int i = m_scroll_view.begin(); i < m_scroll_view.end(); ++i, ++desc_area.m_offset.m_y)
    {
        auto desc = m_recipes[i].m_product.description();
        // Add an arrow to the action under cursor.
        if (i == m_scroll_view.cursorPosition())
        {
            desc += " <==";
        }
        renderString(console, desc, desc_area);
    }
}


} // namespace tradungeon
