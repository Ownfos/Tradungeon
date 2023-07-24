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

    // Refresh the list of tiles that NPCs lie on,
    // so that we can highlight them on rendering procedure.
    void updateNPCPositions(const std::vector<Point>& npc_positions);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;
    virtual void onUpdate(std::chrono::milliseconds delta_time) override;

private:
    // Checks if the given position is inside m_npc_positions.
    bool isNPCPlacedOn(const Point& pos) const;

    Map& m_map;
    Player& m_player;
    const std::vector<CraftRecipe>& m_recipes;

    // List of tiles that NPCs lie on.
    std::vector<Point> m_npc_positions;

    bool m_highlight_interactables{false};
    PeriodicEvent<std::chrono::milliseconds> m_flicker_tiles;
};

} // namespace tradungeon

#endif
