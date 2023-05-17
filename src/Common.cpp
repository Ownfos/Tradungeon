#include "Common.h"

namespace tradungeon
{

Point& Point::operator+=(const Point& other)
{
    m_x += other.m_x;
    m_y += other.m_y;

    return *this;
}

Point& Point::operator-=(const Point& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    
    return *this;
}

Point Point::operator+(const Point& other) const
{
    return {m_x + other.m_x, m_y + other.m_y};
}

Point Point::operator-(const Point& other) const
{
    return {m_x - other.m_x, m_y - other.m_y};
}

} // namespace tradungeon
