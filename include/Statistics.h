#ifndef TRADUNGEON_STATISTICS_H
#define TRADUNGEON_STATISTICS_H

#include "Clock.h"
#include <vector>
#include <any>

namespace tradungeon
{

class Statistics
{
public:
    Statistics();

    int numExitGuidesUsed() const;
    int numFoodEaten() const;
    int numStepsWalked() const;
    int numItemsCrafted() const;
    int numTradesDone() const;
    int netTradeMoney() const;
    const Clock& totalTimeElapsed() const;

private:
    int m_num_exit_guides_used = 0;
    int m_num_food_eaten = 0;
    int m_num_steps_walked = 0;
    int m_num_items_crafted = 0;
    int m_num_trades_done = 0;
    int m_net_trade_money = 0;
    Clock m_total_time_elapsed;

    std::vector<std::any> m_callback_handles;
};

} // namespace tradungeon

#endif
