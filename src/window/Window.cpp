#include "window/Window.h"

namespace tradungeon
{

Window::Window(const Viewport& viewport)
    : m_viewport(viewport)
{}

void Window::clear(TextBuffer& buffer, char boundary, char background)
{
    buffer.fill(background, m_viewport);

    auto [width, height] = m_viewport.m_size;
    auto up = Viewport{m_viewport.m_offset, {width, 1}};
    auto down = Viewport{m_viewport.m_offset + Point{0, height - 1}, {width, 1}};
    auto left = Viewport{m_viewport.m_offset, {1, height}};
    auto right = Viewport{m_viewport.m_offset + Point{width - 1, 0}, {1, height}};
    
    buffer.fill(boundary, up);
    buffer.fill(boundary, down);
    buffer.fill(boundary, left);
    buffer.fill(boundary, right);
}

void Window::renderChar(TextBuffer& buffer, char ch, const Point& pos)
{
    auto abs_pos = pos + m_viewport.m_offset;

    // TODO: throw exception if abs_pos is inside viewport boundary

    buffer.renderChar(ch, abs_pos);
}

void Window::renderString(TextBuffer& buffer, std::string_view str, const Viewport& rel_viewport, TextAlign align)
{
    auto abs_viewport = rel_viewport;
    abs_viewport.m_offset += m_viewport.m_offset;

    // TODO: throw exception if abs_viewport is inside viewport boundary

    buffer.renderString(str, abs_viewport, align);
}

} // namespace tradungeon
