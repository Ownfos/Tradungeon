#ifndef TRADUNGEON_STATUS_WINDOW_H
#define TRADUNGEON_STATUS_WINDOW_H

#include "window/Window.h"
#include "Player.h"
#include "Clock.h"

namespace tradungeon
{

// Displays hunger, thirst, money, and time.
// The viewport height is expected to be 8.
class StatusWindow : public Window
{
public:
    StatusWindow(const Viewport& viewport, Player* player, Clock* clock);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;

private:
    Player* m_player;
    Clock* m_clock;
};

} // namespace tradungeon

#endif
