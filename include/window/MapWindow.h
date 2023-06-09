#ifndef TRADUNGEON_MAP_VIEWER_H
#define TRADUNGEON_MAP_VIEWER_H

#include "window/Window.h"
#include "Map.h"
#include "Player.h"

namespace tradungeon
{

class MapWindow : public Window
{
public:
    MapWindow(const Viewport& viewport, Map* map, Player* player);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;

private:
    Map* m_map;
    Player* m_player;
};

} // namespace tradungeon

#endif
