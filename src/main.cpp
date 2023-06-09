#include "Tests.h"
#include "Console.h"
#include "Game.h"
#include <iostream>

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
        test_interactable();
        return 0;

        auto console = Console();
        auto game = Game();
        std::cout << game.render();

        while(true)
        {
            auto input = console.getKey();
            std::cout << input << std::endl;
            if (input == 'q')
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
