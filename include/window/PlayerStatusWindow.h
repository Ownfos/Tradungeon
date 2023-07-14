#ifndef TRADUNGEON_PLAYER_STATUS_WINDOW_H
#define TRADUNGEON_PLAYER_STATUS_WINDOW_H

#include "window/Window.h"
#include "Player.h"

namespace tradungeon
{

// Displays player's hunger, thirst, and money.
// The viewport height is expected to be 7.
class PlayerStatusWindow : public Window
{
public:
    PlayerStatusWindow(const Viewport& viewport, Player* player);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;

private:
    Player* m_player;
};

} // namespace tradungeon

#endif
