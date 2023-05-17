#include "Console.h"
#include <iostream>

namespace tradungeon
{

Console::Console(Size size)
    : m_size(size)
{
    for (int row = 0; row < m_size.m_height; ++row)
    {
        m_buffer.append(m_size.m_width, ' ');
        m_buffer.append("\n");
    }
}

void Console::print() const
{
    std::cout << m_buffer;
}

void Console::renderChar(char ch, const Point& pos)
{
    m_buffer[pos2Ind(pos)] = ch;
}

void Console::renderString(std::string_view str, const Viewport& viewport)
{
    Point cursor_pos = viewport.m_offset;
    for (char ch : str)
    {
        // Print non-newline character
        if (ch != '\n')
        {
            // Print and move cursor to the right
            renderChar(ch, cursor_pos);
            ++cursor_pos.m_x;
        }

        // If this row is full or a newline character is given,
        // move cursor to the next line's starting point.
        if (ch == '\n' || cursor_pos.m_x >= viewport.m_offset.m_x + viewport.m_size.m_width)
        {
            ++cursor_pos.m_y;
            cursor_pos.m_x = viewport.m_offset.m_x;
        }

        // Ignore overflowing string
        if (cursor_pos.m_y >= viewport.m_offset.m_y + viewport.m_size.m_height)
        {
            return;
        }
    }
}

void Console::fill(char ch, const Viewport& viewport)
{
    for (int x = 0; x < viewport.m_size.m_width; ++x)
    {
        for (int y = 0; y < viewport.m_size.m_height; ++y)
        {
            renderChar(ch, {viewport.m_offset.m_x + x, viewport.m_offset.m_y + y});
        }
    }
}

int Console::pos2Ind(const Point& pos) const
{
    // Each line ends with a newline character '\n',
    // so there are width + 1 characters in a row.
    return pos.m_y * (m_size.m_width + 1) + pos.m_x;
}

} // namespace tradungeon
