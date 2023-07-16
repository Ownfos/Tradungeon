#ifndef TRADUNGEON_PERIODIC_EVENT_H
#define TRADUNGEON_PERIODIC_EVENT_H

#include <functional>

namespace tradungeon
{

// Simulates a timer that invokes a callback periodically.
template<typename TimeUnit>
class PeriodicEvent
{
public:
    PeriodicEvent(TimeUnit period, const std::function<void()>& callback)
        : m_period(period), m_callback(callback)
    {}

    void advanceTime(TimeUnit elapsed_time)
    {
        m_time += elapsed_time;
        while(m_time >= m_period)
        {
            m_callback();

            m_time -= m_period;
        }
    }

private:
    TimeUnit m_period;
    TimeUnit m_time{}; // Assumes that default value is equivalent to 0.

    std::function<void()> m_callback;
};

} // namespace tradungeon

#endif
