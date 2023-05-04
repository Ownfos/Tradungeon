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

void Console::setChar(char value, int x, int y)
{
    m_buffer[pos2Ind(x, y)] = value;
}

char Console::getChar(int x, int y) const
{
    return m_buffer[pos2Ind(x, y)];
}

int Console::pos2Ind(int x, int y) const
{
    // Each line ends with a newline character '\n',
    // so there are width + 1 characters in a row.
    return y * (m_width + 1) + x;
}

} // namespace tradungeon
