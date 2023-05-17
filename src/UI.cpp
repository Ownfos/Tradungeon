#include "UI.h"

namespace tradungeon
{

UI::UI(std::shared_ptr<Console> console, const Viewport& viewport)
    : m_console(console), m_viewport(viewport)
{}

void UI::renderChar(char ch, const Point& pos)
{
    auto abs_pos = pos + m_viewport.m_offset;

    // TODO: throw exception if abs_pos is inside viewport boundary

    m_console->renderChar(ch, abs_pos);
}

void UI::renderString(std::string_view str, const Viewport& rel_viewport)
{
    auto abs_viewport = rel_viewport;
    abs_viewport.m_offset += m_viewport.m_offset;

    // TODO: throw exception if abs_viewport is inside viewport boundary

    m_console->renderString(str, abs_viewport);
}

} // namespace tradungeon
