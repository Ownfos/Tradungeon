#include "Console.h"
#include "Game.h"
#include "Config.h"
#include "AsyncQueue.h"
#include <iostream>
#include <thread>
#include <format>

using namespace tradungeon;

int main()
{
    auto console = Console();
    console.clearScreen();

    auto input_queue = AsyncQueue<int>();
    auto terminate = std::atomic_bool{false};

    auto input_thread = std::thread([&]{
        while(!terminate)
        {
            auto input = console.getKey();

            if (input == 27) // Virtual keycode for 'ESC'
            {
                terminate = true;
                return;
            }
            else
            {
                input_queue.push(input);
            }
        }
    });

    auto render_thread = std::thread([&]{
        try
        {
            auto game = Game();

            while(!terminate)
            {
                std::this_thread::sleep_for(config::delta_time);

                auto input = input_queue.pop();

                if (input.has_value())
                {
                    game.handleInput(input.value());
                }

                game.update(config::delta_time);

                console.setCursor({0, 0});
                std::cout << game.render();

                game.handleWindowAndSceneChanges();
            }
        }
        catch(const std::exception& e)
        {
            terminate = true;
            
            console.clearScreen();
            std::cout << std::format("FATAL ERROR: {}\n", e.what());
        }
    });

    input_thread.join();
    render_thread.join();
}
