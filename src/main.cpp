#include "Tests.h"
#include <iostream>

using namespace tradungeon::test;

int main()
{
    try
    {
        // test_random();
        // test_console();
        // test_market();
        // test_price_fluctuation();
        // test_ui();
        // test_message_log();
        // test_message_log_viewer();
        test_events();
    }
    catch(const std::exception& e)
    {
        std::cout << "FATAL ERROR: " << e.what() << std::endl;
    }
}
