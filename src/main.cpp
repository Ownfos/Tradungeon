#include "Tests.h"
#include "Console.h"
#include "Game.h"
#include <iostream>
#include <sstream>

using namespace tradungeon;
using namespace tradungeon::test;
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
        // auto arr = Array2D<bool>({20, 20}, true);
        // arr[{0,0}] = false;
        // test_path_finding();
        // return 0;

        auto console = Console();
        auto game = Game();

        console.clearScreen();
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
