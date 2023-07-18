#ifndef TRADUNGEON_HELP_WINDOW_H
#define TRADUNGEON_HELP_WINDOW_H

#include "window/Window.h"

namespace tradungeon
{

class HelpWindow : public Window
{
public:
    HelpWindow();

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;
};

} // namespace tradungeon

#endif
