#include "window/CraftRecipeWindow.h"
#include "EventMediator.h"
#include "Config.h"
#include <format>

namespace tradungeon
{

CraftRecipeWindow::CraftRecipeWindow(const Viewport& viewport, const CraftRecipe& recipe, Player& player)
    : Window(viewport), m_recipe(recipe), m_player(player)
{}

bool CraftRecipeWindow::onInput(int keycode)
{
    if (keycode == 'Q')
    {
        EventMediator::m_on_window_pop.signal();
    }
    else if (keycode == 'E')
    {
        if (m_player.calculateAmountCraftable(m_recipe) > 0)
        {
            EventMediator::m_on_item_craft.signal();
            EventMediator::m_on_message.signal(std::format("Crafted {}", m_recipe.m_product.description()));
            m_player.craft(m_recipe);
        }
        else
        {
            EventMediator::m_on_message.signal("Not enough ingredients!");
        }
    }
    return true;
}

void CraftRecipeWindow::onRender(TextBuffer& buffer)
{
    const auto line_area = Size{m_viewport.m_size.m_width, 1};
    renderString(buffer, "Ingredients", Viewport{{0, 1}, line_area}, TextAlign::Center);

    for (int i = 0; i < m_recipe.m_ingredients.size(); ++i)
    {
        const ItemBundle& ingredient = m_recipe.m_ingredients[i];
        renderString(buffer, std::format("{} x{}", ingredient.m_item->description(), ingredient.m_quantity), Viewport{{0, 4 + i}, line_area}, TextAlign::Center);
    }

    renderString(buffer, std::format("press 'E' to craft [x{} left]", m_player.calculateAmountCraftable(m_recipe)), Viewport{{0, m_viewport.m_size.m_height - 2}, line_area}, TextAlign::Center);
}

} // namespace tradungeon
