#include "Common.h"

namespace tradungeon
{

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

int Size::area() const
{
    return m_width * m_height;
}

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

bool Point::isInside(const Size& boundary) const
{
    return m_x >= 0 && m_x < boundary.m_width && m_y >= 0 && m_y < boundary.m_height;
}

} // namespace tradungeon
