#ifndef TRADUNGEON_COMMON_H
#define TRADUNGEON_COMMON_H

namespace tradungeon
{

struct Size
{
    int m_width;
    int m_height;

    Size& operator+=(const Size& other);
    Size& operator-=(const Size& other);

    Size operator+(const Size& other) const;
    Size operator-(const Size& other) const;

    bool operator==(const Size& other) const;

    int area() const;
};

struct Point
{
    int m_x;
    int m_y;

    Point& operator+=(const Point& other);
    Point& operator-=(const Point& other);

    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;

    bool operator==(const Point& other) const;

    bool isInside(const Size& boundary) const;
};

struct Viewport
{
    Point m_offset;
    Size m_size;
};

template<typename T>
T clamp(T min, T max, T value)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

} // namespace tradungeon

#endif
