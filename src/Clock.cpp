#include "Clock.h"

namespace tradungeon
{

int Clock::day() const
{
    return m_time / timeunit::day;
}

int Clock::hour() const
{
    return (m_time % timeunit::day) / timeunit::hour;
}

int Clock::minute() const
{
    return m_time % timeunit::hour;
}

} // namespace tradungeon
