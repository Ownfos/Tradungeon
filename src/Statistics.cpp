#include "Statistics.h"
#include "EventMediator.h"

namespace tradungeon
{

Statistics::Statistics()
{
    m_callback_handles.push_back(EventMediator::m_on_exit_guide.addCallback([this]{
        m_num_exit_guides_used++;
    }));
    m_callback_handles.push_back(EventMediator::m_on_item_trade_confirm.addCallback([this](const Order& order){
        m_num_trades_done++;
        m_net_trade_money += order.m_price;
    }));
    m_callback_handles.push_back(EventMediator::m_on_item_eat.addCallback([this](auto){
        m_num_food_eaten++;
    }));
    m_callback_handles.push_back(EventMediator::m_on_player_walk.addCallback([this](){
        m_num_steps_walked++;
    }));
    m_callback_handles.push_back(EventMediator::m_on_item_craft.addCallback([this](){
        m_num_items_crafted++;
    }));
    m_callback_handles.push_back(EventMediator::m_on_time_elapse.addCallback([this](int elapsed_time){
        m_total_time_elapsed.m_time += elapsed_time;
    }));
}

int Statistics::numExitGuidesUsed() const
{
    return m_num_exit_guides_used;
}

int Statistics::numFoodEaten() const
{
    return m_num_food_eaten;
}

int Statistics::numStepsWalked() const
{
    return m_num_steps_walked;
}

int Statistics::numItemsCrafted() const
{
    return m_num_items_crafted;
}

int Statistics::numTradesDone() const
{
    return m_num_trades_done;
}

int Statistics::netTradeMoney() const
{
    return m_net_trade_money;
}

const Clock& Statistics::totalTimeElapsed() const
{
    return m_total_time_elapsed;
}

} // namespace tradungeon
