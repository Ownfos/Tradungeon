#ifndef TRADUNGEON_CLOCK_H
#define TRADUNGEON_CLOCK_H

namespace tradungeon
{

namespace timeunit
{
    constexpr int hour = 60;
    constexpr int day = hour * 24;
}

struct Clock
{
    // Total elapsed time in minutes.
    int m_time = 0;
    
    // # of days elapsed.
    int day() const;

    // # of hours elapsed since the beginning of this day.
    // Note: the return value ranges from 0 to 23.
    int hour() const;
    
    // # of minutes elpased since the beginning of this hour.
    // Note: the return value ranges from 0 to 59.
    int minute() const;
};

} // namespace tradungeon

#endif
