#include "Map.h"
#include "DiamondSquare.h"
#include <map>
#include <limits>

namespace tradungeon
{

Map::Map(const Size& size)
    : m_tiles(size), m_interactables(size)
{
    reset();
}

Size Map::size() const
{
    return m_tiles.size();
}

Tile Map::tileset(const Point& pos) const
{
    return m_tiles[pos];
}

const std::vector<std::shared_ptr<Interactable>>& Map::interactables(const Point& pos) const
{
    return m_interactables[pos];
}

void Map::addInteractable(const Point& pos, std::shared_ptr<Interactable> interactable)
{
    m_interactables[pos].push_back(interactable);
}

void Map::removeInteractable(const Point& pos, Interactable* interactable)
{
    auto is_same = [interactable](const std::shared_ptr<Interactable>& ptr){
        return ptr.get() == interactable;
    };

    auto& v = m_interactables[pos];
    v.erase(std::remove_if(v.begin(), v.end(), is_same), v.end());
}

bool Map::isMovable(const Point& pos) const
{
    switch(tileset(pos))
    {
    case Tile::Lava:
    case Tile::Wall:
    case Tile::Empty:
        return false;
        
    default:
        return true;
    }
}

void Map::reset()
{

    // Defines the upper limit of noise map value for a tileset to be assigned.
    // Starting from the tile type with lowest threshold,
    // we will assign the type if noise map value is lower than the threshold.
    auto threshold_config = std::vector<std::pair<Tile, double>>{
        {Tile::Water, 0.2},
        {Tile::Mud, 0.3},
        {Tile::Dirt, 1.0},
        {Tile::Rock, 0.5},
        {Tile::Water, 0.2},
        {Tile::Rock, 0.5},
        {Tile::OreVein, 0.7},
        {Tile::Rock, 0.5},
        {Tile::Lava, 1.0},
    };

    auto tileset_threshold = std::map<double, Tile>();
    auto max = 0.0;
    for (int i=0; i<threshold_config.size(); ++i)
    {
        max += threshold_config[i].second;
        tileset_threshold.insert({max, threshold_config[i].first});

        auto next_tileset = i == threshold_config.size() - 1 ? Tile::Wall : threshold_config[i+1].first;
        tileset_threshold.insert({-max, next_tileset});
    }
    tileset_threshold.insert({std::numeric_limits<double>::max(), Tile::Wall});


    // Generate a random height map bigger than m_tiles.
    // Note that diamond-square algorithm only works when # edges = 2^n.
    auto [width, height] = m_tiles.size();
    auto max_edge_length = std::max(width, height);

    auto noise_map_size = 2;
    while (noise_map_size < max_edge_length)
    {
        noise_map_size *= 2;
    }
    auto noise_map = diamondSquare(noise_map_size, 0, max, 0.7);

    // Categorize tile types using noise map.
    for (int y=0;y<height;++y)
    {
        for (int x=0;x<width;++x)
        {
            // Find the first tile type that has higher threshold than noise map value.
            //
            // This loop is guaranteed to assign one tile type
            // since std::map iteration is done in ascending order
            // and the last element of tileset_threshold
            // is the numerical maximum for double type.
            auto pos = Point{x, y};
            for (auto [threshold, type] : tileset_threshold)
            {
                if (noise_map[pos] < threshold)
                {
                    m_tiles[pos] = type;
                    break;
                }
            }
        }
    }
}

void Map::groupSimilarTileset(int threshold)
{
    auto result = m_tiles;

    auto [width, height] = m_tiles.size();
    for (int y=1;y<height-1;++y)
    {
        for (int x=1;x<width-1;++x)
        {
            // Count the tileset for 8 adjacent tiles.
            auto tileset_count = std::map<Tile, int>();
            auto offsets = std::vector<Point>{
                {-1, 0},
                {1, 0},
                {0, -1},
                {0, 1},
                {-1, -1},
                {-1, 1},
                {1, -1},
                {1, 1},
            };
            for (const auto& offset : offsets)
            {
                auto neighbor = Point{x, y} + offset;
                tileset_count[m_tiles[neighbor]]++;
            }

            // Get the tileset that occured the most.
            auto comp = [](const auto& lhs, const auto&rhs){
                return lhs.second < rhs.second;
            };
            auto [tileset, count] = *std::max_element(
                tileset_count.begin(),
                tileset_count.end(),
                comp
            );

            // If the tileset is dominant, make current tile have the same type.
            if (count >= threshold)
            {
                m_tiles[{x, y}] = tileset;
            }
        }
    }
}

} // namespace tradungeon
