#ifndef TRADUNGEON_CRAFT_RECIPE_H
#define TRADUNGEON_CRAFT_RECIPE_H

#include "interactable/Item.h"

namespace tradungeon
{

struct CraftRecipe
{
    std::vector<ItemBundle> m_ingredients;
    ItemBundle m_product;
};

} // namespace tradungeon

#endif
