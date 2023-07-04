#include "Tests.h"
#include "TextBuffer.h"
#include "Console.h"
#include "Random.h"
#include "window/WindowManager.h"
#include "window/MessageLogWindow.h"
#include "Event.h"
#include "Array2D.h"
#include "interactable/DroppedItem.h"
#include "Inventory.h"
#include "EventMediator.h"
#include "PathFinding.h"
#include <iostream>
#include <numeric>
#include <cassert>

namespace tradungeon::test
{

TestUI::TestUI(const Viewport& viewport, int id)
    : Window(viewport), m_id(id)
{}

bool TestUI::onInput(int keycode)
{
    std::cout << "Window #" << m_id << " received input " << keycode << std::endl;
    return false;
}

void TestUI::onRender(TextBuffer& buffer)
{
    renderChar(buffer, '@', {0, 0});
    renderString(buffer, "hahahoho", {{1,1},{3,3}});
}

TestAction::TestAction(std::string&& description)
    : m_description(std::move(description))
{}

void TestAction::execute()
{
    std::cout << "executed action: " << m_description << std::endl;
}

std::string TestAction::description() const
{
    return m_description;
}

TestInteractable::TestInteractable(std::string&& description)
    : m_description(std::move(description))
{}

std::string TestInteractable::description() const
{
    return m_description;
}

std::vector<std::shared_ptr<Action>> TestInteractable::availableActions() const
{
    return {
        std::make_shared<TestAction>("talk"),
        std::make_shared<TestAction>("attack"),
        std::make_shared<TestAction>("flee")
    };
}

TestItem::TestItem(std::string name, int id, int weight)
    : m_name(name), m_id(id), m_weight(weight)
{}

int TestItem::id() const
{
    return m_id;
}

int TestItem::weight() const
{
    return m_weight;
}

std::string TestItem::description() const
{
    return m_name;
}

std::vector<std::shared_ptr<Action>> TestItem::availableActions() const
{
    return {
        std::make_shared<TestAction>("Use"),
        std::make_shared<TestAction>("Throw")
    };
}

void test_random()
{
    for(int i=0;i<100;++i)
    {
        std::cout << Random::range(0, 4);
    }

    auto sample = Random::sample(std::vector{11,22,33,44,55}, 3);
    Random::shuffle(sample);

    std::cout << "\n";
    for (auto s : sample)
    {
        std::cout << s << " ";
    }
    std::cout << "\n";
}

void test_text_buffer()
{
    auto buffer = TextBuffer({20, 10});
    buffer.renderChar('#', {0, 0});
    buffer.renderChar('#', {19, 0});
    buffer.renderChar('#', {0, 9});
    buffer.renderChar('#', {19, 9});
    std::cout << buffer.getContent();

    buffer.renderChar('@', {19, 9});
    std::cout << buffer.getContent();

    buffer.renderString("hello, world!\nnewline test\n\nnewline test newline test newline test", {{4, 2}, {15, 5}});
    std::cout << buffer.getContent();
}

void test_console()
{
    auto console = Console();
    console.setCursor({5, 2});
    std::cout << console.getKey() << std::endl;
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


void test_price_fluctuation()
{
    // Initial settings
    auto simulator = MarketSimulator{};
    simulator.m_items = {
        {11, "Lemon", 100, 30, 30, 70},
        {44, "Apple", 200, 30, 30, 10},
    };
    simulator.m_users = {
        {1234, "Jenny"},
        {7777, "Robert"},
        {5678, "Jackson"},
        {3579, "David"},
        {2684, "Laura"},
    };

    // Randomize item preference.
    for (auto& item : simulator.m_items)
    {
        // Select 4 random users
        auto selected = Random::sample(simulator.m_users, 4);
        Random::shuffle(selected);

        // Make an item preference for each one
        auto preferences = std::vector<Preference>{};
        for (const auto& user : selected)
        {
            auto pref = Preference{};
            pref.m_user_id = user.m_id;
            pref.m_degree = Random::range(50, 100);
            pref.m_desired_price = item.m_initial_price + Random::range(-20, 20);

            preferences.push_back(pref);

            // std::cout << user.m_name << " wants to trade " << item.m_name << " at " << pref.m_desired_price << " with degree of " << pref.m_degree << "\n";
        }

        // First two will buy the item, while the others sell.
        item.m_buyers.insert(item.m_buyers.end(), preferences.begin(), preferences.begin() + 2);
        item.m_sellers.insert(item.m_sellers.end(), preferences.begin() + 2, preferences.end());
    }

    // Simulate 10 days of market trade
    for (int day = 0; day < 50; ++day)
    {
        if (day == 25)
        {
            simulator.m_items[0].m_desired_net_demand -= 30;
            simulator.m_items[1].m_desired_net_demand += 30;
        }

        std::cout << "[day " << day << "]\n\n";

        for (auto& item : simulator.m_items)
        {
            auto orders = std::vector<Order>{};

            // Prepare buy orders
            double total_demand_degree = std::accumulate(item.m_buyers.begin(), item.m_buyers.end(), 0.0, [](auto sum, auto pref){ return sum + pref.m_degree; });
            for (auto& pref : item.m_buyers)
            {
                auto order = Order{};
                order.m_type = OrderType::Buy;
                order.m_item_id = item.m_id;
                order.m_user_id = pref.m_user_id;
                order.m_price = pref.m_desired_price;
                order.m_quantity = item.m_net_demand * pref.m_degree / total_demand_degree;

                orders.push_back(order);
            }

            // Prepare sell orders
            double total_supply_degree = std::accumulate(item.m_sellers.begin(), item.m_sellers.end(), 0.0, [](auto sum, auto pref){ return sum + pref.m_degree; });
            for (auto& pref : item.m_sellers)
            {
                auto order = Order{};
                order.m_type = OrderType::Sell;
                order.m_item_id = item.m_id;
                order.m_user_id = pref.m_user_id;
                order.m_price = pref.m_desired_price;
                order.m_quantity = item.m_net_supply * pref.m_degree / total_supply_degree;

                orders.push_back(order);
            }

            // Simulate trade
            simulator.m_market.clear_orders();

            Random::shuffle(orders);
            for (auto order : orders)
            {
                std::cout << (order.m_type == OrderType::Buy ? "Buy " : "Sell ") << order.m_quantity << " " << item.m_name << " for " << order.m_price << std::endl;
                if (auto result = simulator.m_market.register_order(order); result.has_value())
                {
                    std::cout << order.m_quantity << " " << item.m_name << " were " << (order.m_type == OrderType::Buy ? "bought" : "sold") << " for " << result->m_sell_order.m_price << " gold" << std::endl;
                }
            }

            // Adjust desired price
            for (auto& pref : item.m_sellers)
            {
                auto remaining_orders = simulator.m_market.get_user_orders(pref.m_user_id);
                if (remaining_orders.size() > 0)
                {
                    pref.m_desired_price -= Random::range(1, 5);
                }
                else
                {
                    pref.m_desired_price += Random::range(1, 5);
                }
            }
            for (auto& pref : item.m_buyers)
            {
                auto remaining_orders = simulator.m_market.get_user_orders(pref.m_user_id);
                if (remaining_orders.size() > 0)
                {
                    pref.m_desired_price += Random::range(1, 5);
                }
                else
                {
                    pref.m_desired_price -= Random::range(1, 5);
                }
            }

            // Check unresolved net supply and demand
            auto unresolved_supplies = simulator.m_market.get_sell_queue(item.m_id);
            auto net_unresolved_supply = std::accumulate(unresolved_supplies.begin(), unresolved_supplies.end(), 0, [](auto sum, auto order){ return sum + order.m_quantity; });
            std::cout << "Unresolved supply: " << net_unresolved_supply << " / " << item.m_net_supply << std::endl;

            auto unresolved_demands = simulator.m_market.get_buy_queue(item.m_id);
            auto net_unresolved_demand = std::accumulate(unresolved_demands.begin(), unresolved_demands.end(), 0, [](auto sum, auto order){ return sum + order.m_quantity; });
            std::cout << "Unresolved demand: " << net_unresolved_demand << " / " << item.m_net_demand << std::endl;

            // Adjust net supply and demand up to 1~10% of the difference
            auto extra_supply = net_unresolved_supply - net_unresolved_demand;
            item.m_net_supply -= extra_supply * Random::range(1, 10) / 100;

            // Force net demand to reach desired level
            item.m_net_demand += (item.m_desired_net_demand - item.m_net_demand) * 4 / 10;

            std::cout << std::endl;
            // break; // Test with only one item for now.
        }
    }
}

void test_ui()
{
    auto console = TextBuffer({80, 25});
    auto ui_manager = WindowManager();
    ui_manager.push(std::make_shared<TestUI>(Viewport{{0, 0}, {80, 25}}, 1));
    ui_manager.push(std::make_shared<TestUI>(Viewport{{5, 10}, {5, 5}}, 2));
    
    ui_manager.render(console);
    ui_manager.handleInput(12345);
    std::cout << console.getContent();

    ui_manager.pop();
    ui_manager.render(console);
    ui_manager.handleInput(12345);
    std::cout << console.getContent();
}

void test_message_log()
{
    auto log = MessageLog({20, 5});
    log.push("Hi");
    log.push("Hello, World!");
    log.push("A very long string that overflows");
    std::cout << log.size() << std::endl;
    std::cout << log.getLines(0, 3);

    log.push("asdf");
    log.push("asdf");
    log.push("asdf");
    log.push("asdf");
    std::cout << log.size() << std::endl;
    std::cout << log.getLines(0, 3);
}

void test_message_log_viewer()
{
    auto buffer = TextBuffer({80, 7});
    auto ui_manager = WindowManager();
    auto msg_viewer = std::make_shared<MessageLogWindow>(Viewport{{0, 0}, {80, 7}}, 20);

    ui_manager.push(msg_viewer);
    ui_manager.render(buffer);
    std::cout << buffer.getContent();

    msg_viewer->push("Single Line");
    ui_manager.render(buffer);
    std::cout << buffer.getContent();

    msg_viewer->scrollDown();
    ui_manager.render(buffer);
    std::cout << buffer.getContent();

    msg_viewer->scrollUp();
    ui_manager.render(buffer);
    std::cout << buffer.getContent();

    for (int i=0;i<10;++i)
    {
        msg_viewer->push("Hello, World!" + std::to_string(i));
    }
    ui_manager.render(buffer);
    std::cout << buffer.getContent();

    msg_viewer->scrollUp();
    msg_viewer->scrollUp();
    ui_manager.render(buffer);
    std::cout << buffer.getContent();
}

void test_events()
{
    auto event = Event<std::string>();
    auto cb1 = event.addCallback([](const std::string& message){ std::cout << message << std::endl; });
    auto cb2 = event.addCallback([](const std::string& message){ std::cout << message.size() << std::endl; });
    event.signal("Hello, World!");

    cb2->removeFromEvent();
    event.signal("Removed second callback");
    
    cb1->removeFromEvent();
    event.signal("Removed first callback");
}

void test_render_loop()
{
    auto console = Console();
    auto buffer = TextBuffer({20, 20});
    for (char ch = 'a'; ch <= 'e'; ++ch)
    {
        // Render this frame
        buffer.fill(ch);
        console.setCursor({0, 0});
        std::cout << buffer.getContent();

        // Wait for input
        console.getKey();
    }
}

void test_array2d()
{
    auto arr1 = Array2D<int>({2, 5});
    arr1[{0, 1}] = 12345;
    std::cout << arr1[{0, 0}] << " " << arr1[{0, 1}] << std::endl;
    arr1.fill(777);
    std::cout << arr1[{0, 0}] << " " << arr1[{0, 1}] << std::endl;

    auto arr2 = Array2D<char>({3, 3}, '#');
    std::cout << arr2[{2, 0}] << " " << arr2[{1, 2}] << std::endl;
}

void test_map_generation()
{
    auto print_map = [](const auto& map){
        auto [width, height] = map.size();
        for (int y=0; y<height; ++y)
        {
            for (int x=0; x<width; ++x)
            {
                std::cout << static_cast<char>(map.tileset({x, y}));
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    };

    auto map = Map({100, 400});
    print_map(map);

    // map.groupSimilarTileset(6);
    map.groupSimilarTileset(5);

    print_map(map);
}

void test_interactable()
{
    auto map = Map({10, 10});

    auto jack = std::make_shared<TestInteractable>("Jack");
    auto robinson = std::make_shared<TestInteractable>("Robinson");

    map.addInteractable({1, 1}, jack);
    map.addInteractable({1, 1}, robinson);

    for (const auto& interactable : map.interactables({1, 1}))
    {
        std::cout << interactable->description() << std::endl;
        for (const auto& action : interactable->availableActions())
        {
            std::cout << action->description() << std::endl;
        }
    }

    map.removeInteractable({1, 1}, jack.get());

    for (const auto& interactable : map.interactables({1, 1}))
    {
        std::cout << interactable->description() << std::endl;
    }
}

void test_inventory()
{
    auto inventory = Inventory();
    auto print_inventory = [&](){
        std::cout << "Net weight: " << inventory.netWeight() << std::endl;
        for (int i = 0; i < inventory.numSlots(); ++i)
        {
            const auto& item_bundle = inventory.itemBundleAtSlot(i);
            std::cout << item_bundle.m_item->description() << " (x" << item_bundle.m_quantity << ") - " << item_bundle.weight() << std::endl;
            
            for (auto& action : item_bundle.m_item->availableActions())
            {
                std::cout << action->description() << std::endl;
            }
        }
        std::cout << std::endl;
    };

    // Test indivitual function.
    auto apple = std::make_shared<TestItem>("Apple", 1, 4);
    auto potion = std::make_shared<TestItem>("Potion", 2, 20);

    print_inventory();

    inventory.addItem({apple, 50});
    inventory.addItem({potion, 3});
    print_inventory();

    inventory.removeItem({apple, 20});
    print_inventory();

    inventory.removeItem({potion, 3});
    print_inventory();

    assert(inventory.numSlots() == 1);
    assert(inventory.itemBundleWithID(1)->get().m_quantity == 30);
    assert(inventory.itemBundleWithID(2).has_value() == false);
}

void test_path_finding()
{
    auto print_path = [](const std::optional<Path>& path) {
        if (!path.has_value())
        {
            std::cout << "No path was found" << std::endl;
        }
        else
        {
            std::cout << "Path length: " << path->size() << std::endl;
            for (const Point& p : path.value())
            {
                std::cout << "(" << p.m_x << ", " << p.m_y << ") ";
            }
            std::cout << std::endl;
        }
    };

    auto map = Array2D<int>({1000, 1000}, 1);

    print_path(dijkstra(map, {0, 0}, {5, 5}));

    map[{1, 0}] = 0;
    map[{1, 1}] = 0;
    print_path(dijkstra(map, {0, 0}, {5, 5}));
}

} // namespace tradungeon::test
