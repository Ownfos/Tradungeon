
#ifndef TRADUNGEON_TESTS_H
#define TRADUNGEON_TESTS_H

#include "Market.h"
#include "Map.h"
#include "window/Window.h"
#include "interactable/Item.h"
#include "MarketSimulator.h"
#include <vector>
#include <string>

namespace tradungeon::test
{

void test_random();
void test_text_buffer();
void test_console();
void test_market();
void test_price_fluctuation();
void test_market_simulator();
void test_ui();
void test_message_log();
void test_message_log_viewer();
void test_events();
void test_render_loop();
void test_array2d();
void test_map_generation();
void test_interactable();
void test_inventory();
void test_path_finding();

struct Preference
{
    int m_user_id;
    int m_degree;
    int m_desired_price;
};

struct Item
{
    int m_id;
    std::string m_name;
    int m_initial_price;
    int m_net_supply;
    int m_net_demand;
    int m_desired_net_demand;
    std::vector<Preference> m_buyers;
    std::vector<Preference> m_sellers;
};

struct User
{
    int m_id;
    std::string m_name;
};

class TestTrader : public Trader
{
public:
    TestTrader(int id, std::string name);

    virtual int id() const override;
    virtual const std::vector<Order>& remainingOrders() const override;
    virtual void pushOrder(const Order& order) override;
    virtual void clearOrders() override;

// private:
    int m_id;
    std::string m_name;
    std::vector<Order> m_orders;
};

struct MarketSimulator
{
    std::vector<Item> m_items;
    std::vector<User> m_users;
    Market m_market;
};

class TestUI : public Window
{
public:
    TestUI(const Viewport& viewport, int id);

    virtual bool onInput(int keycode) override;
    virtual void onRender(TextBuffer& console) override;

private:
    int m_id;
};

class TestAction : public Action
{
public:
    TestAction(std::string&& description);

    virtual void execute() override;
    virtual std::string description() const override;

private:
    std::string m_description;
};

class TestInteractable : public Interactable
{
public:
    TestInteractable(std::string&& description);

    virtual std::string description() const override;
    virtual std::vector<std::shared_ptr<Action>> availableActions() const override;
    
private:
    std::string m_description;
};

class TestItem : public tradungeon::Item
{
public:
    TestItem(std::string name, int id, int weight);

    virtual int id() const override;
    virtual int weight() const override;
    virtual std::string description() const override;
    virtual std::vector<std::shared_ptr<Action>> availableActions() const override;

private:
    std::string m_name;
    int m_id;
    int m_weight;
};

} // namespace tradungeon::test

#endif
