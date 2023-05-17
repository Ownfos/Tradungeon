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
    Console(Size size);
    void print() const;

    void renderChar(char ch, const Point& pos);

    // Prints a multi-line string to a given region.
    // Overflowing string is handled in following manner:
    //   Horizontal overflow => automatic newline
    //   Vertical overflow   => stop rendering (ignores remainder)
    //
    // Escape sequence except '\n' is NOT supported!
    void renderString(std::string_view str, const Viewport& viewport);

    // Fills a region with given character.
    void fill(char ch, const Viewport& viewport);

private:
    // Convert coordinates to corresponding index in buffer.
    int pos2Ind(const Point& pos) const;

    Size m_size;
    std::string m_buffer;
};

} // namespace tradungeon

#endif
