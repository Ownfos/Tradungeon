#include "Tests.h"
#include "Console.h"
#include "Game.h"
#include "EventMediator.h"
#include "Config.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <queue>
#include <mutex>

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

        auto input_queue = std::queue<int>();
        auto input_mutex = std::mutex();

        auto terminate = std::atomic_bool{false};

        auto input_thread = std::thread([&]{
            while(true)
            {
                auto input = console.getKey();

                if (input == 27)
                {
                    terminate = true;
                    return;
                }
                else
                {
                    auto lg = std::lock_guard(input_mutex);
                    input_queue.push(input);
                }
            }
        });

        auto render_thread = std::thread([&]{
            auto game = Game();

            console.clearScreen();
            std::cout << game.render();

            while(!terminate)
            {
                std::this_thread::sleep_for(config::delta_time);

                auto input = std::optional<int>();
                {
                    auto lg = std::unique_lock(input_mutex);
                    if (!input_queue.empty())
                    {
                        input = input_queue.front();
                        input_queue.pop();
                    }
                };

                if (input.has_value())
                {
                    game.handleInput(input.value());
                    // EventMediator::m_on_message.signal("Input: " + std::to_string(input.value()));
                }

                game.update(config::delta_time);

                console.setCursor({0, 0});
                std::cout << game.render();
            }
        });

        input_thread.join();
        render_thread.join();
    }
    catch(const std::exception& e)
    {
        std::cout << "FATAL ERROR: " << e.what() << std::endl;
    }
}
