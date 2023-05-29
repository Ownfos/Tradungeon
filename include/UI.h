#ifndef TRADUNGEON_UI_H
#define TRADUNGEON_UI_H

#include "TextBuffer.h"
#include "Common.h"

namespace tradungeon
{

class UI
{
public:
    UI(const Viewport& viewport);
    virtual ~UI() = default;

    virtual bool onInput(int keycode) = 0;
    virtual void onRender(TextBuffer& console) = 0;

    void clear(TextBuffer& console, char boundary, char background);
    void renderChar(TextBuffer& console, char ch, const Point& rel_pos);
    void renderString(TextBuffer& console, std::string_view str, const Viewport& rel_viewport);

private:
    Viewport m_viewport;
};

} // namespace tradungeon

#endif
