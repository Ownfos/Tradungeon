#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

namespace tradungeon
{

// Console is a buffer that helps printing characters on specific position.
// A whole screen is treated as a single std::string instance.
// (0, 0) points to the left-top corner.
class Console
{
public:
    Console(int width, int height);
    void print() const;
    void setChar(char value, int x, int y);
    char getChar(int x, int y) const;

private:
    // Convert coordinates to corresponding index in buffer.
    int pos2Ind(int x, int y) const;

    int width;
    int height;
    std::string buffer;
};

} // namespace tradungeon

#endif
