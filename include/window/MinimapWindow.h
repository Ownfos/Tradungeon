#ifndef TRADUNGEON_MINIMAP_WINDOW_H
#define TRADUNGEON_MINIMAP_WINDOW_H

#include "window/Window.h"
#include "Map.h"
#include "Player.h"

namespace tradungeon
{

class MinimapWindow : public Window
{
public:
    MinimapWindow(const Viewport& viewport, Map& map, Player& player);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;

private:
    // Calculates the position of a pixel we should sample
    // if we were to render a texture into a square surface.
    Point textureCoordinate(const Size& texture_size, const Size& surface_size, const Point& surface_coord);

    Map& m_map;
    Player& m_player;
};

} // namespace tradungeon

#endif
