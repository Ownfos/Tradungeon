#include "UI.h"

namespace tradungeon
{

UI::UI(std::shared_ptr<Console> console, const Viewport& viewport)
    : m_console(console), m_viewport(viewport)
{}

void UI::clear(char boundary, char background)
{
    m_console->fill(background, m_viewport);

    auto [width, height] = m_viewport.m_size;
    auto up = Viewport{m_viewport.m_offset, {width, 1}};
    auto down = Viewport{m_viewport.m_offset + Point{0, height - 1}, {width, 1}};
    auto left = Viewport{m_viewport.m_offset, {1, height}};
    auto right = Viewport{m_viewport.m_offset + Point{width - 1, 0}, {1, height}};
    
    m_console->fill(boundary, up);
    m_console->fill(boundary, down);
    m_console->fill(boundary, left);
    m_console->fill(boundary, right);
}

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
