#ifndef TRADUNGEON_CONSOLE_H
#define TRADUNGEON_CONSOLE_H

#include "Common.h"
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

    void renderChar(char ch, const Point& pos);
    void renderString(std::string_view str, const Viewport& viewport);

private:
    // Convert coordinates to corresponding index in buffer.
    int pos2Ind(const Point& pos) const;

    int m_width;
    int m_height;
    std::string m_buffer;
};

} // namespace tradungeon

#endif
