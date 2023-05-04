#include "Console.h"
#include "Market.h"
#include <iostream>

using namespace tradungeon;

void test_console()
{
    auto console = Console(20, 10);
    console.setChar('#', 0, 0);
    console.setChar('#', 19, 0);
    console.setChar('#', 0, 9);
    console.setChar('#', 19, 9);
    console.print();

    console.setChar('@', 19, 9);
    console.print();
}

void test_market()
{
    auto order_list = std::vector<Order>{
        {OrderType::Buy, 0, 0, 10, 55},
        {OrderType::Buy, 0, 1, 3, 100},
        {OrderType::Sell, 1, 0, 7, 50},
        {OrderType::Sell, 2, 0, 5, 45},
        {OrderType::Buy, 1, 0, 1, 47},
    };

    auto name_dict = std::map<int, std::string>{
        {0, "John"},
        {1, "Peter"},
        {2, "Harry"},
    };

    auto item_dict = std::map<int, std::string>{
        {0, "Apple"},
        {1, "Lemon"},
    };

    auto market = Market{};

    for (auto order : order_list)
    {
        std::cout << "Processing order...\n\n";
        if (auto result = market.register_order(order); result.has_value())
        {
            std::cout << "[Contract]\n";
            std::cout << "buyer: " << name_dict[result->m_buy_order.m_user_id] << "\n";
            std::cout << "seller: " << name_dict[result->m_sell_order.m_user_id] << "\n";
            std::cout << "item: " << item_dict[result->m_buy_order.m_item_id] << "\n";
            std::cout << "quantity: " << result->m_buy_order.m_quantity << "\n";
            std::cout << "price range: " << result->m_sell_order.m_price << " ~ " << result->m_buy_order.m_price << "\n\n";
        }
    }

    for (auto [user_id, name] : name_dict)
    {
        auto remaining_orders = market.get_user_orders(user_id);
        for (auto order : remaining_orders)
        {
            std::cout << "[Remaining order]\n";
            std::cout << "buyer: " << name << "\n";
            std::cout << "type: " << (order.m_type == OrderType::Buy ? "Buy" : "Sell") << "\n";
            std::cout << "item: " << item_dict[order.m_item_id] << "\n";
            std::cout << "quantity: " << order.m_quantity << "\n";
            std::cout << "price: " << order.m_price << "\n\n";
        }
    }
}

int main()
{
    try
    {
        // test_console();
        test_market();
    }
    catch(const std::exception& e)
    {
        std::cout << "FATAL ERROR: " << e.what() << std::endl;
    }
}
