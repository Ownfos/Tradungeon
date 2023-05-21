#include "UI.h"

namespace tradungeon
{

UI::UI(const Viewport& viewport)
    : m_viewport(viewport)
{}

void UI::clear(Console& console, char boundary, char background)
{
    console.fill(background, m_viewport);

    auto [width, height] = m_viewport.m_size;
    auto up = Viewport{m_viewport.m_offset, {width, 1}};
    auto down = Viewport{m_viewport.m_offset + Point{0, height - 1}, {width, 1}};
    auto left = Viewport{m_viewport.m_offset, {1, height}};
    auto right = Viewport{m_viewport.m_offset + Point{width - 1, 0}, {1, height}};
    
    console.fill(boundary, up);
    console.fill(boundary, down);
    console.fill(boundary, left);
    console.fill(boundary, right);
}

void UI::renderChar(Console& console, char ch, const Point& pos)
{
    auto abs_pos = pos + m_viewport.m_offset;

    // TODO: throw exception if abs_pos is inside viewport boundary

    console.renderChar(ch, abs_pos);
}

void UI::renderString(Console& console, std::string_view str, const Viewport& rel_viewport)
{
    auto abs_viewport = rel_viewport;
    abs_viewport.m_offset += m_viewport.m_offset;

    // TODO: throw exception if abs_viewport is inside viewport boundary

    console.renderString(str, abs_viewport);
}

} // namespace tradungeon
