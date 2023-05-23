#ifndef TRADUNGEON_TEXT_BUFFER_H
#define TRADUNGEON_TEXT_BUFFER_H

#include "Common.h"
#include <string>

namespace tradungeon
{

// TextBuffer is a 2d buffer that helps printing characters on specific position.
// A whole screen is treated as a single std::string instance.
// (0, 0) points to the left-top corner.
class TextBuffer
{
public:
    TextBuffer(Size size);

    void renderChar(char ch, const Point& pos);

    // Prints a multi-line string to a given region.
    // Overflowing string is handled in following manner:
    //   Horizontal overflow => automatic newline
    //   Vertical overflow   => stop rendering (ignores remainder)
    //
    // Escape sequences except '\n' are NOT supported!s
    void renderString(std::string_view str, const Viewport& viewport);

    // Fills a region with given character.
    void fill(char ch, const Viewport& viewport);

    // Fills whole buffer with givene character.
    void fill(char ch);

    Size getSize() const;
    std::string_view getContent() const;

private:
    // Convert coordinates to corresponding index in buffer.
    int pos2Ind(const Point& pos) const;

    Size m_size;
    std::string m_buffer;
};

} // namespace tradungeon

#endif
