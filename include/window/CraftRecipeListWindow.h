#ifndef TRADUNGEON_CRAFT_RECIPE_LIST_WINDOW_H
#define TRADUNGEON_CRAFT_RECIPE_LIST_WINDOW_H

#include "window/Window.h"
#include "Player.h"
#include "CraftRecipe.h"
#include "ScrollView.h"

namespace tradungeon
{

class CraftRecipeListWindow : public Window
{
public:
    CraftRecipeListWindow(const Viewport& viewport, const std::vector<CraftRecipe>& recipes, Player& player);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;

private:
    const std::vector<CraftRecipe>& m_recipes;
    Player& m_player;
    ScrollView m_scroll_view;
};

} // namespace tradungeon

#endif
