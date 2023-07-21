#ifndef TRADUNGEON_GENERATING_MAP_WINDOW_H
#define TRADUNGEON_GENERATING_MAP_WINDOW_H

#include "window/Window.h"
#include "PeriodicEvent.h"

namespace tradungeon
{

// A small pop-up window that displays 'Generating map...'.
// Since Map::reset() takes few seconds, we need to let the user know that the game is not frozen.
class GeneratingMapWindow : public Window
{
public:
    GeneratingMapWindow();

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;
    virtual void onUpdate(std::chrono::milliseconds delta_time) override;

private:
    bool m_flicker = true;
    PeriodicEvent<std::chrono::milliseconds> m_flicker_timer;
};

} // namespace tradungeon

#endif
