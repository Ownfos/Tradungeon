#ifndef TRADUNGEON_ARRAY_2D_H
#define TRADUNGEON_ARRAY_2D_H

#include "Common.h"
#include <vector>
#include <algorithm>

namespace tradungeon
{

template<typename T>
class Array2D
{
public:
    Array2D(const Size& size)
        : m_size(size), m_data(size.area())
    {}

    Array2D(const Size& size, const T& value)
        : m_size(size), m_data(size.area(), value)
    {}

    Array2D(const Array2D&) = default;
    Array2D(Array2D&&) = default;
    Array2D& operator=(const Array2D&) = default;
    Array2D& operator=(Array2D&&) = default;
    ~Array2D() noexcept = default;

    T& operator[](const Point& indices)
    {
        if (!indices.isInside(m_size))
        {
            throw std::exception("Index out of range");
        }

        return m_data[indices.m_x * m_size.m_height + indices.m_y];
    }

    const T& operator[](const Point& indices) const
    {
        if (!indices.isInside(m_size))
        {
            throw std::exception("Index out of range");
        }

        return m_data[indices.m_x * m_size.m_height + indices.m_y];
    }

    void fill(const T& value)
    {
        std::fill(m_data.begin(), m_data.end(), value);
    }

    Size size() const
    {
        return m_size;
    }

private:
    Size m_size;
    std::vector<T> m_data;
};

} // namespace tradungeon

#endif
