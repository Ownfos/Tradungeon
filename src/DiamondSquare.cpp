#include "DiamondSquare.h"
#include "Random.h"

namespace tradungeon
{

bool isPowerOfTwo(int value)
{
    return value >= 1 && !(value & (value - 1));
}

void diamondStep(Array2D<double>& map, const Point& pos, int patch_size, double rand_range)
{
    auto half = patch_size / 2;
    auto offsets = std::vector<Point>{
        {-half, -half},
        {half, -half},
        {-half, half},
        {half, half}
    };

    auto avg = 0.0;
    for (const auto& offset : offsets)
    {
        avg += map[pos + offset];
    }
    avg /= 4.0;

    map[pos] = avg + Random::range(-rand_range, rand_range);
}

void squareStep(Array2D<double>& map, const Point& pos, int patch_size, double rand_range)
{
    auto half = patch_size / 2;
    auto offsets = std::vector<Point>{
        {-half, 0},
        {half, 0},
        {0, -half},
        {0, half}
    };

    auto avg = 0.0;
    auto count = 0;
    for (const auto& offset : offsets)
    {
        auto neighbor = pos + offset;
        if (neighbor.isInside(map.size()))
        {
            avg += map[neighbor];
            ++count;
        }
    }
    avg /= count;

    map[pos] = avg + Random::range(-rand_range, rand_range);
}

Array2D<double> diamondSquare(int num_edge, double bias, double rand_range, double rand_decay)
{
    if (!isPowerOfTwo(num_edge))
    {
        throw std::exception("There should be 2^n edges");
    }

    // Initialize map with random corners.
    auto ret = Array2D<double>({num_edge + 1, num_edge + 1});
    ret[{0, 0}] = bias + Random::range(-rand_range, rand_range);
    ret[{num_edge, 0}] = bias + Random::range(-rand_range, rand_range);
    ret[{0, num_edge}] = bias + Random::range(-rand_range, rand_range);
    ret[{num_edge, num_edge}] = bias + Random::range(-rand_range, rand_range);

    for (int patch_size = num_edge; patch_size > 1; patch_size /= 2)
    {
        // Diamond step
        for (int i = patch_size / 2; i <= num_edge; i += patch_size)
        {
            for (int j = patch_size / 2; j <= num_edge; j += patch_size)
            {
                diamondStep(ret, {i, j}, patch_size, rand_range);
            }
        }

        // Fix the center at bias (i.e., ignore the result of diamond step at first iteration)
        if (patch_size == num_edge)
        {
            ret[{num_edge / 2, num_edge / 2}] = bias;
        }

        // Square step
        for (int i = patch_size / 2; i <= num_edge; i += patch_size)
        {
            for (int j = 0; j <= num_edge; j += patch_size)
            {
                squareStep(ret, {i, j}, patch_size, rand_range);
                squareStep(ret, {j, i}, patch_size, rand_range);
            }
        }

        // Decrease randomness exponentially
        rand_range *= rand_decay;
    }

    return ret;
}

} // namespace tradungeon
