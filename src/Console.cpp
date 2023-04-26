#include "Console.h"
#include <iostream>

namespace tradungeon
{

Console::Console(int width, int height)
    : width(width), height(height)
{
    for (int row = 0; row < height; ++row)
    {
        buffer.append(width, ' ');
        buffer.append("\n");
    }
}

void Console::print() const
{
    std::cout << buffer;
}

void Console::setChar(char value, int x, int y)
{
    buffer[pos2Ind(x, y)] = value;
}

char Console::getChar(int x, int y) const
{
    return buffer[pos2Ind(x, y)];
}

int Console::pos2Ind(int x, int y) const
{
    // Each line ends with a newline character '\n',
    // so there are width + 1 characters in a row.
    return y * (width + 1) + x;
}

} // namespace tradungeon
