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

    // Prevent object slicing.
    UI(const UI&) = delete;
    UI(UI&&) = delete;
    UI& operator=(const UI&) = delete;
    UI& operator=(UI&&) = delete;

    virtual ~UI() = default;

    virtual bool onInput(int keycode) = 0;
    virtual void onRender(TextBuffer& buffer) = 0;

    void clear(TextBuffer& buffer, char boundary, char background);
    void renderChar(TextBuffer& buffer, char ch, const Point& rel_pos);
    void renderString(TextBuffer& buffer, std::string_view str, const Viewport& rel_viewport);

protected:
    const Viewport m_viewport;
};

} // namespace tradungeon

#endif
