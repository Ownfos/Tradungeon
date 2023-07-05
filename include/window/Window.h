#ifndef TRADUNGEON_WINDOW_H
#define TRADUNGEON_WINDOW_H

#include "Polymorphic.h"
#include "TextBuffer.h"
#include "Common.h"
#include <chrono>

namespace tradungeon
{

class Window : private Polymorphic
{
public:
    Window(const Viewport& viewport);

    virtual bool onInput(int keycode) = 0;
    virtual void onRender(TextBuffer& buffer) = 0;
    virtual void onUpdate(std::chrono::milliseconds delta_time) {};

    void clear(TextBuffer& buffer, char boundary, char background);
    void renderChar(TextBuffer& buffer, char ch, const Point& rel_pos);
    void renderString(TextBuffer& buffer, std::string_view str, const Viewport& rel_viewport, TextAlign align = TextAlign::Left);

protected:
    const Viewport m_viewport;
};

} // namespace tradungeon

#endif
