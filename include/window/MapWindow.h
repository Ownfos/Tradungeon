#ifndef TRADUNGEON_MAP_WINDOW_H
#define TRADUNGEON_MAP_WINDOW_H

#include "window/Window.h"
#include "Map.h"
#include "Player.h"
#include "PeriodicEvent.h"
#include "CraftRecipe.h"

namespace tradungeon
{

class MapWindow : public Window
{
public:
    MapWindow(const Viewport& viewport, Map& map, Player& player, const std::vector<CraftRecipe>& recipes);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;
    virtual void onUpdate(std::chrono::milliseconds delta_time) override;

private:
    Map& m_map;
    Player& m_player;
    const std::vector<CraftRecipe>& m_recipes;

    bool m_highlight_interactables{false};
    PeriodicEvent<std::chrono::milliseconds> m_flicker_tiles;
};

} // namespace tradungeon

#endif
