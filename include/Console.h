#ifndef TRADUNGEON_CONSOLE_H
#define TRADUNGEON_CONSOLE_H

#include "Common.h"
#include <Windows.h>

namespace tradungeon
{

// Console handles Windows specific console input and output,
// such as positioning cursor and receiving keystrokes.
class Console
{
public:
    Console();

    // Wait for a key press event and return its ascii code.
    // This is a blocking funciton, so it will not return until something is pressed.
    int getKey();

    // Moves the cursor position of console.
    void setCursor(const Point& pos);

private:
    HANDLE m_input_handle;
    HANDLE m_output_handle;
};

} // namespace tradungeon

#endif
