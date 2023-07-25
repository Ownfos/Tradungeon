#ifndef TRADUNGEON_GAMEOVER_WINDOW_H
#define TRADUNGEON_GAMEOVER_WINDOW_H

#include "window/Window.h"
#include "Statistics.h"

namespace tradungeon
{

class GameoverWindow : public Window
{
public:
    GameoverWindow(std::unique_ptr<Statistics>&& statistics, const std::string& ending_description);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;

private:
    std::unique_ptr<Statistics> m_statistics;
    std::string m_ending_description;
};

} // namespace tradungeon

#endif
