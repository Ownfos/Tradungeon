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
#include "interactable/DummyItem.h"
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

std::vector<std::shared_ptr<Action>> TestInteractable::availableActions()
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

std::vector<std::shared_ptr<Action>> TestItem::availableActions()
{
    return {
        std::make_shared<TestAction>("Use"),
        std::make_shared<TestAction>("Throw")
    };
}

TestTrader::TestTrader(int id, std::string name)
    : m_id(id), m_name(name)
{}

int TestTrader::id() const
{
    return m_id;
}

const std::vector<Order>& TestTrader::remainingOrders() const
{
    return m_orders;
}

void TestTrader::pushOrder(const Order& order)
{
    m_orders.push_back(order);
    std::cout << "[Assign Order]\n";
    std::cout << "who: " << m_name << "\n";
    std::cout << "type: " << (order.m_type == OrderType::Buy ? "Buy" : "Sell") << "\n";
    std::cout << "item id: " << order.m_item->id() << "\n";
    std::cout << "quantity: " << order.m_quantity << "\n";
    std::cout << "price: " << order.m_price << "\n\n";
}

void TestTrader::clearOrders()
{
    m_orders.clear();
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
    auto items = std::vector{
        std::make_shared<DummyItem>("Apple", 0, 1),
        std::make_shared<DummyItem>("Lemon", 1, 1)
    };
    auto users = std::vector{
        std::make_shared<TestTrader>(0, "John"),
        std::make_shared<TestTrader>(1, "Peter"),
        std::make_shared<TestTrader>(2, "Harry"),
    };
    auto order_list = std::vector<Order>{
        {OrderType::Buy, users[0], items[0], 10, 55},
        {OrderType::Buy, users[0], items[1], 3, 100},
        {OrderType::Sell, users[1], items[0], 7, 50},
        {OrderType::Sell, users[2], items[0], 5, 45},
        {OrderType::Buy, users[1], items[0], 1, 47},
    };

    auto market = Market{};

    for (auto order : order_list)
    {
        std::cout << "Processing order...\n\n";
        if (auto result = market.register_order(order); result.has_value())
        {
            std::cout << "[Contract]\n";
            std::cout << "buyer: " << users[result->m_buy_order.m_user->id()]->m_name << "\n";
            std::cout << "seller: " << users[result->m_sell_order.m_user->id()]->m_name << "\n";
            std::cout << "item: " << items[result->m_buy_order.m_item->id()]->description() << "\n";
            std::cout << "quantity: " << result->m_buy_order.m_quantity << "\n";
            std::cout << "price range: " << result->m_sell_order.m_price << " ~ " << result->m_buy_order.m_price << "\n\n";
        }
    }
}

void test_market_simulator()
{
    auto traders = std::vector<std::shared_ptr<Trader>>{
        std::make_shared<TestTrader>(0, "trader#0"),
        std::make_shared<TestTrader>(1, "trader#1"),
        std::make_shared<TestTrader>(2, "trader#2"),
        std::make_shared<TestTrader>(3, "trader#3"),
        std::make_shared<TestTrader>(4, "trader#4"),
    };
    auto simulator = tradungeon::MarketSimulator(traders);
    simulator.registerTradableItem(ItemConfig{
        std::make_shared<TestItem>("Apple", 0, 1),
        10, // demand
        20, // supply
        1000, // initial price
        2, // # buyers
        2 // # sellers 
    });

    for (int i=0;i<100;++i)
    {
        std::cout << "Day " << i << std::endl;
        simulator.generateDailyOrders();
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

    // Test text overflow handling.
    msg_viewer->push(std::string(100, '*'));
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
