#include "Console.h"
#include <string>
#include <exception>

namespace tradungeon
{

Console::Console()
    : m_input_handle(GetStdHandle(STD_INPUT_HANDLE)),
    m_output_handle(GetStdHandle(STD_OUTPUT_HANDLE))
{}

int Console::getKey()
{
    // Keep reading input events until we find a key press event.
    auto input_record = INPUT_RECORD{};
    auto num_events_reads = DWORD{};
    while (true)
    {
        // ReadConsoleInput should return nonzero value on success,
        // but sometimes it returns 0 while GetLastError() says it was successful (ERROR_SUCCESS).
        if (ReadConsoleInput(m_input_handle, &input_record, 1, &num_events_reads) != 0 && GetLastError() != 0)
        {
            throw std::exception(("ReadConsoleInput() failed with error code " + std::to_string(GetLastError())).c_str());
        }

        // Since other events like window buffer resize or focus comes in,
        // we need to wait for a key press event specifically.
        if (input_record.EventType == KEY_EVENT && input_record.Event.KeyEvent.bKeyDown)
        {
            return input_record.Event.KeyEvent.wVirtualKeyCode;
        }
    }
}

void Console::setCursor(const Point& pos)
{
    auto coord = COORD{
        static_cast<short>(pos.m_x),
        static_cast<short>(pos.m_y)
    };
    SetConsoleCursorPosition(m_output_handle, coord);
}

void Console::clearScreen()
{
    // Screen filling algorithm from stack overflow.
    // https://stackoverflow.com/questions/5866529/how-do-we-clear-the-console-in-assembly/5866648#5866648
    COORD tl = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    GetConsoleScreenBufferInfo(m_output_handle, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(m_output_handle, ' ', cells, tl, &written);
    FillConsoleOutputAttribute(m_output_handle, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(m_output_handle, tl);
}

} // namespace tradungeon
