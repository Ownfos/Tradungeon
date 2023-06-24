#include "Tests.h"
#include "Console.h"
#include "Game.h"
#include <iostream>
#include <sstream>

using namespace tradungeon;
using namespace tradungeon::test;

void render(std::string str, int width, TextAlign align)
{
    auto lines = std::vector<std::string>();
    auto line_buffer = std::ostringstream();

    auto line_length = 0;
    for (char ch : str)
    {
        // Print non-newline character
        if (ch != '\n')
        {
            line_buffer << ch;
            ++line_length;
        }

        // If this row is full or a newline character is given,
        // move cursor to the next line's starting point.
        if (ch == '\n' || line_length >= width)
        {
            lines.push_back(line_buffer.str());
            line_buffer.clear();
            line_buffer.str("");
            line_length = 0;
        }
    }
    // Flush remaining tokens.
    lines.push_back(line_buffer.str());


    auto buffer = TextBuffer({width, 2});
    auto view = Viewport{{0, 0}, {width, 1}};
    for (auto& line : lines)
    {
        if (view.m_offset.m_y >= 2) break;

        // Calculate horizontal offset according to alignment.
        view.m_offset.m_x = 0;
        if (align == TextAlign::Right)
        {
            view.m_offset.m_x = width - line.length();
        }
        else if (align == TextAlign::Center)
        {
            view.m_offset.m_x = (width - line.length()) / 2;
        }

        buffer.renderString(line, view);
        // std::cout << line << std::endl;

        view.m_offset.m_y += 1;
    }

    std::cout << buffer.getContent();
}

int main()
{
    try
    {
        // test_random();
        // test_text_buffer();
        // test_console();
        // test_market();
        // test_price_fluctuation();
        // test_ui();
        // test_message_log();
        // test_message_log_viewer();
        // test_events();
        // test_render_loop();
        // test_array2d();
        // test_map_generation();
        // test_interactable();
        // test_inventory();
        // render("hello\nworld!\n\n", 10, TextAlign::Left);
        // render("hello\nworld!\n\n", 10, TextAlign::Right);
        // render("hello\nworld!\n\n", 10, TextAlign::Center);
        // return 0;

        auto console = Console();
        auto game = Game();
        std::cout << game.render();

        while(true)
        {
            auto input = console.getKey();
            std::cout << input << std::endl;
            if (input == 27) // Virtual keycode for ESC
            {
                break;
            }

            game.handleInput(input);

            console.setCursor({0, 0});
            std::cout << game.render();
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "FATAL ERROR: " << e.what() << std::endl;
    }
}
