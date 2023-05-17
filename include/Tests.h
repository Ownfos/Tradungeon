
#ifndef TRADUNGEON_TESTS_H
#define TRADUNGEON_TESTS_H

#include "Market.h"
#include <vector>
#include <string>

namespace tradungeon::test
{

void test_random();
void test_console();
void test_market();
void test_price_fluctuation();

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

struct MarketSimulator
{
    std::vector<Item> m_items;
    std::vector<User> m_users;
    Market m_market;
};

} // namespace tradungeon::test

#endif
