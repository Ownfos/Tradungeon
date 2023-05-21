#ifndef TRADUNGEON_UI_H
#define TRADUNGEON_UI_H

#include "Console.h"
#include "Common.h"

namespace tradungeon
{

class UI
{
public:
    UI(const Viewport& viewport);
    virtual ~UI() = default;

    // virtual void onInput() = 0;
    virtual void onRender(Console& console) = 0;

    void clear(Console& console, char boundary, char background);
    void renderChar(Console& console, char ch, const Point& rel_pos);
    void renderString(Console& console, std::string_view str, const Viewport& rel_viewport);

private:
    Viewport m_viewport;
};

} // namespace tradungeon

#endif
