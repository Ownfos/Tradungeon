#ifndef TRADUNGEON_TITLE_MENU_WINDOW_H
#define TRADUNGEON_TITLE_MENU_WINDOW_H

#include "window/Window.h"
#include "PeriodicEvent.h"

namespace tradungeon
{

class TitleMenuWindow : public Window
{
public:
    TitleMenuWindow(const Viewport& viewport);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;
    virtual void onUpdate(std::chrono::milliseconds delta_time) override;

private:
    int m_cursor_pos = 0;
    bool m_flicker_text = true;
    PeriodicEvent<std::chrono::milliseconds> m_flicker_text_timer;
};

} // namespace tradungeon

#endif
