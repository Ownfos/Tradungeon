#include "Map.h"
#include "DiamondSquare.h"
#include <iostream>
#include <map>
#include <limits>

namespace tradungeon
{

Map::Map(const Size& size)
    : m_tiles(size)
{
    reset();
}

void Map::reset()
{
    auto [width, height] = m_tiles.size();
    auto max_edge_length = std::max(width, height);

    // Generate a random height map bigger than m_tiles.
    // Note that diamond-square algorithm only works when # edges = 2^n.
    auto noise_map_size = 2;
    while (noise_map_size < max_edge_length)
    {
        noise_map_size *= 2;
    }
    auto noise_map = diamondSquare(noise_map_size, 5, 6, 0.7);

    // Defines the upper limit of noise map value for a tileset to be assigned.
    // Starting from the tile type with lowest threshold,
    // we will assign the type if noise map value is lower than the threshold.
    auto tileset_threshold = std::map<double, Tile>{
        {0.0, Tile::Water},
        {3.0, Tile::Mud},
        {5.0, Tile::Dirt},
        {7.0, Tile::Rock},
        {9.0, Tile::OreVein},
        {11.0, Tile::Lava},
        {std::numeric_limits<double>::max(), Tile::Lava},
    };

    // Categorize tile types using noise map.
    for (int j=0;j<height;++j)
    {
        for (int i=0;i<width;++i)
        {
            // Find the first tile type that has higher threshold than noise map value.
            //
            // This loop is guaranteed to assign one tile type
            // since std::map iteration is done in ascending order
            // and the last element of tileset_threshold
            // is the numerical maximum for double type.
            auto pos = Point{i, j};
            for (auto [threshold, type] : tileset_threshold)
            {
                if (noise_map[pos] < threshold)
                {
                    m_tiles[pos] = type;
                    std::cout << static_cast<char>(type);
                    break;
                }
            }
        }
        std::cout << std::endl;
    }
    // TODO: fill m_tiles using noise_map.
}

} // namespace tradungeon
