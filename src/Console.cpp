#include "Console.h"
#include <iostream>

namespace tradungeon
{

Console::Console(int width, int height)
    : m_width(width), m_height(height)
{
    for (int row = 0; row < height; ++row)
    {
        m_buffer.append(width, ' ');
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
    Point cursor_pos = viewport.offset;
    for (char ch : str)
    {
        // Print non-newline character
        if (ch != '\n')
        {
            // Print and move cursor to the right
            renderChar(ch, cursor_pos);
            ++cursor_pos.x;
        }

        // If this row is full or a newline character is given,
        // move cursor to the next line's starting point.
        if (ch == '\n' || cursor_pos.x >= viewport.offset.x + viewport.size.width)
        {
            ++cursor_pos.y;
            cursor_pos.x = viewport.offset.x;
        }

        // Ignore overflowing string
        if (cursor_pos.y >= viewport.offset.y + viewport.size.height)
        {
            return;
        }
    }
}

int Console::pos2Ind(const Point& pos) const
{
    // Each line ends with a newline character '\n',
    // so there are width + 1 characters in a row.
    return pos.y * (m_width + 1) + pos.x;
}

} // namespace tradungeon
