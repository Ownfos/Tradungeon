#ifndef TRADUNGEON_RANDOM_H
#define TRADUNGEON_RANDOM_H

#include "Common.h"
#include <random>
#include <algorithm>
#include <vector>

namespace tradungeon
{

// A random number generator using seed given by std::random_device.
// This class uses static member variable to keep global random number generator.
class Random
{
public:
    // Returns a random integer in an interval [begin, end) using uniform distribution.
    static int range(int begin, int end);

    // Returns a random real number in an inverval [begin, end) using uniform distribution.
    static double range(double begin, double end);

    // Returns a random point inside a rectacle with given size.
    // Coordinates will be in range [0, width) and [0, height) accordingly.
    static Point pointInRect(const Size& rect_size);

    static std::vector<int> sample_indices(int num_elements, int n);

    template<typename Container, typename T = typename Container::value_type>
    static auto sample(const Container& container, int n)
    {
        auto ret = std::vector<T>{};
        std::sample(container.cbegin(), container.cend(), std::back_inserter(ret), n, m_generator);

        return ret;
    }

    template<typename Container, typename T = typename Container::value_type>
    static void shuffle(Container& container)
    {
        std::shuffle(container.begin(), container.end(), m_generator);
    }

private:
    static std::mt19937 m_generator;
};

} // namespace tradungeon

#endif
