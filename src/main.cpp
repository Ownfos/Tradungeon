#include "Tests.h"
#include "Console.h"
#include "Game.h"
#include "EventMediator.h"
#include "Config.h"
#include "AsyncQueue.h"
#include "scene/GameplayScene.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <format>

using namespace tradungeon;
using namespace tradungeon::test;

void test()
{
    try
    {
        test_random();
        test_text_buffer();
        test_console();
        test_market();
        test_market_simulator();
        test_ui();
        test_message_log();
        test_message_log_viewer();
        test_events();
        test_render_loop();
        test_array2d();
        test_map_generation();
        test_interactable();
        test_inventory();
        test_path_finding();
    }
    catch(const std::exception& e)
    {
        std::cout << std::format("FATAL ERROR: {}\n", e.what());
    }
}

int main()
{
    auto console = Console();

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

            console.clearScreen();
            std::cout << game.render();

            while(!terminate)
            {
                std::this_thread::sleep_for(config::delta_time);

                auto input = input_queue.pop();

                if (input.has_value())
                {
                    game.handleInput(input.value());
                    // EventMediator::m_on_message.signal("Input: " + std::to_string(input.value()));
                }

                game.update(config::delta_time);

                console.setCursor({0, 0});
                std::cout << game.render();
            }
        }
        catch(const std::exception& e)
        {
            terminate = true;
            std::cout << std::format("FATAL ERROR: {}\n", e.what());
        }
    });

    input_thread.join();
    render_thread.join();
}
