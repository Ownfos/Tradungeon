#ifndef TRADUNGEON_CRAFT_RECIPE_WINDOW_H
#define TRADUNGEON_CRAFT_RECIPE_WINDOW_H

#include "window/Window.h"
#include "Player.h"
#include "CraftRecipe.h"

namespace tradungeon
{

class CraftRecipeWindow : public Window
{
public:
    CraftRecipeWindow(const Viewport& viewport, const CraftRecipe& recipe, Player& player);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;

private:
    const CraftRecipe& m_recipe;
    Player& m_player;
};

} // namespace tradungeon

#endif
