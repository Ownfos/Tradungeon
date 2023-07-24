#include "Map.h"
#include "DiamondSquare.h"
#include "Random.h"
#include "Config.h"
#include "interactable/Exit.h"
#include "interactable/DroppedItem.h"
#include "interactable/EdibleItems.h"
#include "interactable/UnusableItems.h"
#include <map>
#include <limits>
#include <array>

namespace tradungeon
{

Map::Map(const Size& size, int exit_min_distance, int exit_max_distance)
    : m_squared_exit_min_dist(exit_min_distance * exit_min_distance),
    m_squared_exit_max_dist(exit_max_distance * exit_max_distance),
    m_tiles(size),
    m_visibility(size, false),
    m_interactables(size)
{}

Size Map::size() const
{
    return m_tiles.size();
}

Tile Map::tileset(const Point& pos) const
{
    return m_tiles[pos];
}

Point Map::exitPosition() const
{
    return m_exit_pos;
}

const std::vector<std::shared_ptr<Interactable>>& Map::interactables(const Point& pos) const
{
    return m_interactables[pos];
}

void Map::addInteractable(const Point& pos, std::shared_ptr<Interactable> interactable)
{
    m_interactables[pos].push_back(interactable);
}

void Map::removeInteractable(const Point& pos, const Interactable* interactable)
{
    auto is_same = [interactable](const std::shared_ptr<Interactable>& ptr){
        return ptr.get() == interactable;
    };

    auto& v = m_interactables[pos];
    v.erase(std::remove_if(v.begin(), v.end(), is_same), v.end());
}

void Map::expandVisibility(const Point& pos, int radius)
{
    auto square_radius = radius * radius;
    for (int dx = -radius; dx <= radius; ++dx)
    {
        for (int dy = -radius; dy <= radius; ++dy)
        {
            auto p = pos + Point{dx, dy};
            auto square_dist = dx * dx + dy * dy;
            if (square_dist <= square_radius && p.isInside(m_tiles.size()))
            {
                m_visibility[p] = true;
            }
        }
    }
}

bool Map::isMovable(const Point& pos) const
{
    return isMovableTileset(tileset(pos));
}

bool Map::isVisible(const Point& pos) const
{
    return m_visibility[pos];
}

bool Map::isMovableTileset(Tile tile)
{
    return tile != Tile::Wall;
}

void Map::reset()
{
    generateTileset();

    // Reduce noise to generate smoother terrain.
    for (int i = 0; i < 2; ++i)
    {
        groupSimilarTileset(5);
    }

    // Try to select a valid exit point.
    // If we fail, recursively repeat the reset process.
    if (trySpawnExit() == false)
    {
        reset();
        return;
    }

    spawnItems();
}

void Map::generateTileset()
{
    // Defines the upper limit of noise map value for a tileset to be assigned.
    // Starting from the tile type with lowest threshold,
    // we will assign the type if noise map value is lower than the threshold.
    auto threshold_config = std::vector<std::pair<Tile, double>>{
        {Tile::Water, 0.05},
        {Tile::Mud, 0.1},
        {Tile::Dirt, 0.3},
        {Tile::Rock, 0.3},
        {Tile::Water, 0.2},
        {Tile::Rock, 0.2},
        {Tile::OreVein, 0.7},
        {Tile::Rock, 0.1},
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
    auto noise_map = diamondSquare(noise_map_size, 0, 3, 0.81);
    noise_map.normalize();

    // Categorize tile types using noise map.
    // The center of noise map will be aligned to the center of this map.
    auto size_diff = noise_map.size() - m_tiles.size();
    auto offset = Point{size_diff.m_width / 2, size_diff.m_height / 2};
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
                if (noise_map[pos + offset] < threshold)
                {
                    m_tiles[pos] = type;
                    break;
                }
            }

            // Remove remaining interactables if any.
            m_interactables[pos].clear();

            // Make tiles invisible at the beginning.
            m_visibility[pos] = false;
        }
    }
}

bool Map::trySpawnExit()
{
    const auto center = Point{
        m_tiles.size().m_width / 2,
        m_tiles.size().m_height / 2
    };

    // Try to find a point satisfying distance constraint
    // that is reachable from the center of the map.
    //
    // Since there is no guarantee that such point exists,
    // we will consider it impossible after several trials.
    for(int i = 0; i < config::num_trials_spawn_exit; ++i)
    {
        // Pick a random point.
        m_exit_pos = Random::pointInRect(m_tiles.size());
        
        // Check if the point meets the min/max exit distance constraint.
        auto diff = m_exit_pos - center;
        auto squared_distance = diff.dotProduct(diff);
        if (squared_distance < m_squared_exit_min_dist || squared_distance > m_squared_exit_max_dist)
        {
            continue;
        }

        // Check if the point is reachable from the center of the map.
        if (!findPath(center, m_exit_pos))
        {
            continue;
        }

        // Succeeded finding a valid exit.
        m_tiles[m_exit_pos] = Tile::Exit;
        addInteractable(m_exit_pos, std::make_shared<Exit>());
        return true;
    }

    // Failed to find a valid exit.
    return false;
}

void Map::spawnItems()
{
    // Tile type, spawn probability, maximum quantity per spawn, item
    auto item_spawn_table = std::vector<std::tuple<Tile, double, int, std::shared_ptr<Item>>>{
        {Tile::Dirt, 0.003, 1, std::make_shared<Apple>()},
        {Tile::Dirt, 0.003, 3, std::make_shared<WoodStick>()},
        {Tile::Mud, 0.003, 1, std::make_shared<Clam>()},
        {Tile::Rock, 0.003, 1, std::make_shared<IronOre>()},
        {Tile::Rock, 0.02, 1, std::make_shared<Coal>()},
        {Tile::OreVein, 0.01, 1, std::make_shared<SilverOre>()},
        {Tile::OreVein, 0.01, 1, std::make_shared<GoldOre>()},
        {Tile::OreVein, 0.001, 1, std::make_shared<Diamond>()},
    };

    auto [width, height] = m_tiles.size();
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            auto pos = Point{x, y};
            auto tile = tileset(pos);
            for (auto  [type, prob, max_quantity, item] : item_spawn_table)
            {
                if (type == tile && Random::range(0.0, 1.0) < prob)
                {
                    addInteractable(pos, std::make_shared<DroppedItem>(ItemBundle{item, Random::range(1, max_quantity + 1)}));
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
            constexpr auto offsets = std::array<Point, 8>{
                Point{-1, 0},
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

std::optional<Path> Map::findPath(const Point& start, const Point& end) const
{
    auto movable = m_tiles.transform<int>([](auto tile){ return isMovableTileset(tile); });
    return dijkstra(movable, start, end);
}

} // namespace tradungeon
