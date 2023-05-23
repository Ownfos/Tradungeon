#include "TextBuffer.h"
#include <iostream>

namespace tradungeon
{

TextBuffer::TextBuffer(Size size)
    : m_size(size)
{
    for (int row = 0; row < m_size.m_height; ++row)
    {
        m_buffer.append(m_size.m_width, ' ');
        m_buffer.append("\n");
    }
}

void TextBuffer::renderChar(char ch, const Point& pos)
{
    m_buffer[pos2Ind(pos)] = ch;
}

void TextBuffer::renderString(std::string_view str, const Viewport& viewport)
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

void TextBuffer::fill(char ch, const Viewport& viewport)
{
    for (int x = 0; x < viewport.m_size.m_width; ++x)
    {
        for (int y = 0; y < viewport.m_size.m_height; ++y)
        {
            renderChar(ch, {viewport.m_offset.m_x + x, viewport.m_offset.m_y + y});
        }
    }
}

void TextBuffer::fill(char ch)
{
    fill(ch, {{0, 0}, m_size});
}

int TextBuffer::pos2Ind(const Point& pos) const
{
    // Each line ends with a newline character '\n',
    // so there are width + 1 characters in a row.
    return pos.m_y * (m_size.m_width + 1) + pos.m_x;
}

Size TextBuffer::getSize() const
{
    return m_size;
}

std::string_view TextBuffer::getContent() const
{
    return m_buffer;
}

} // namespace tradungeon
