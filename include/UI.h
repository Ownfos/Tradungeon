#ifndef TRADUNGEON_UI_H
#define TRADUNGEON_UI_H

#include "Console.h"
#include "Common.h"
#include <memory>

namespace tradungeon
{

class UI
{
public:
    UI(std::shared_ptr<Console> console, const Viewport& viewport);
    virtual ~UI() = default;

    // virtual void onInput() = 0;
    virtual void onRender() = 0;

protected:
    void renderChar(char ch, const Point& rel_pos);
    void renderString(std::string_view str, const Viewport& rel_viewport);

private:
    std::shared_ptr<Console> m_console;
    Viewport m_viewport;
};

} // namespace tradungeon

#endif
