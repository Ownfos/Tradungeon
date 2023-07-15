#ifndef TRADUNGEON_ARRAY_2D_H
#define TRADUNGEON_ARRAY_2D_H

#include "Common.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>

namespace tradungeon
{

// A wrapper class that helps utilize 2d array efficiently.
// This class is implemented using one dimentional container and Point <-> index conversion.
//
// Array2D<bool> is not supported because std::vector<bool>::operator[] doesn't give bool reference.
// Consider using int as an alternative data type.
// Read the answer to the stackoverflow question below for more details.
// - https://stackoverflow.com/questions/63476664/what-does-the-error-return-cannot-convert-from-std-vb-referencestd-wrap
template<typename T>
class Array2D
{
    // Make Array2D with other datatype friend
    // so that we can access m_data at Array2D::transform() function.
    template<typename U>
    friend class Array2D;

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

    // Modify the elements to make mean = 0 and standard deviation = 1.
    // Only available for float or double type.
    // Z = (X - mu) / sigma (mu: average, sigma: standard deviation)
    template<typename = std::enable_if_t<std::is_floating_point_v<T>>>
    void normalize()
    {
        auto avg = std::accumulate(m_data.begin(), m_data.end(), 0.0) / m_data.size();
        auto variance = std::accumulate(m_data.begin(), m_data.end(), 0.0, [=](auto sum, auto value){
            return (value - avg) * (value - avg);
        });
        auto standard_deviation = std::sqrt(variance);

        for (auto& value : m_data)
        {
            value = (value - avg) / standard_deviation;
        }
    }

    template<typename U>
    Array2D<U> transform(const std::function<U(const T&)>& op) const
    {
        auto ret = Array2D<U>(m_size);
        for (int i = 0; i < m_data.size(); ++i)
        {
            ret.m_data[i] = op(m_data[i]);
        }
        return ret;
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
