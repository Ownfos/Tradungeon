#ifndef TRADUNGEON_COMMON_H
#define TRADUNGEON_COMMON_H

namespace tradungeon
{

struct Point
{
    int m_x;
    int m_y;

    Point& operator+=(const Point& other);
    Point& operator-=(const Point& other);

    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
};

struct Size
{
    int m_width;
    int m_height;
};

struct Viewport
{
    Point m_offset;
    Size m_size;
};

} // namespace tradungeon

#endif
