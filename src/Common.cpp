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

Size& Size::operator+=(const Size& other)
{
    m_width += other.m_width;
    m_height += other.m_height;

    return *this;
}

Size& Size::operator-=(const Size& other)
{
    m_width -= other.m_width;
    m_height -= other.m_height;

    return *this;
}

Size Size::operator+(const Size& other) const
{
    return {m_width + other.m_width, m_height + other.m_height};
}

Size Size::operator-(const Size& other) const
{
    return {m_width - other.m_width, m_height - other.m_height};
}

} // namespace tradungeon
