#include "Random.h"
#include <numeric>

namespace tradungeon
{

std::mt19937 Random::m_generator{std::random_device{}()};

int Random::range(int begin, int end)
{
    return std::uniform_int_distribution(begin, end-1)(m_generator);
}

double Random::range(double begin, double end)
{
    return std::uniform_real_distribution(begin, end)(m_generator);
}

Point Random::pointInRect(const Size& rect_size)
{
    return {range(0, rect_size.m_width), range(0, rect_size.m_height)};
}

std::vector<int> Random::sample_indices(int num_elements, int n)
{
    std::vector<int> indices(num_elements);
    std::iota(indices.begin(), indices.end(), 0);

    return sample(indices, n);
}

} // namespace tradungeon
