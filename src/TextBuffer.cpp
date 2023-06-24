#include "TextBuffer.h"
#include <vector>
#include <sstream>

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

void TextBuffer::renderString(std::string_view str, const Viewport& viewport, TextAlign align)
{
    // Split given string into a smaller token if it overflows viewport width.
    // After this process, each element in 'lines' are guaranteed to fit in the viewport.
    // This allows us to easily calculate offsets required to implement text alignment.
    auto lines = std::vector<std::string>();
    auto line_buffer = std::ostringstream();
    // Current size of line_buffer content.
    // Note that 'line_buffer.str().size()' will cause copy, which is obviously inefficient.
    auto line_length = 0;

    for (char ch : str)
    {
        // Non-newline characters are just appended to the buffer.
        if (ch != '\n')
        {
            line_buffer << ch;
            ++line_length;
        }

        // If this row is full or a newline character is given,
        // flush the buffer to store it as a complete line.
        if (ch == '\n' || line_length >= viewport.m_size.m_width)
        {
            lines.push_back(line_buffer.str());

            // Resetting stringstream requires both functions (I'm not sure why).
            line_buffer.clear();
            line_buffer.str("");

            line_length = 0;
        }
    }
    // Flush the remaining tokens.
    // Without this, some cases like single line output won't be handled correctly.
    lines.push_back(line_buffer.str());

    // Now that we know the content of each line,
    // apply text alignment to get appropriate offset and print them!
    Point cursor_pos = viewport.m_offset;
    for (auto& line : lines)
    {
        // Ignore vertical overflows.
        if (cursor_pos.m_y >= viewport.m_offset.m_y + viewport.m_size.m_height)
        {
            return;
        }

        // Calculate offset required for specified text alignment.
        if (align == TextAlign::Left)
        {
            cursor_pos.m_x = viewport.m_offset.m_x;
        }
        else if (align == TextAlign::Right)
        {
            cursor_pos.m_x = viewport.m_offset.m_x + (viewport.m_size.m_width - line.length());
        }
        else if (align == TextAlign::Center)
        {
            cursor_pos.m_x = viewport.m_offset.m_x + (viewport.m_size.m_width - line.length()) / 2;
        }

        // Print characters one by one.
        for (auto ch : line)
        {
            renderChar(ch, cursor_pos);
            ++cursor_pos.m_x;
        }

        // Move to the next line.
        ++cursor_pos.m_y;
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
