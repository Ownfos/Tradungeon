#ifndef TRADUNGEON_MAP_H
#define TRADUNGEON_MAP_H

#include "Array2D.h"
#include "PathFinding.h"
#include "interactable/Interactable.h"
#include <numeric>

namespace tradungeon
{

enum class Tile : char
{
    Water = '~',
    Mud = '/',
    Dirt = ' ',
    Rock = '`',
    OreVein = '-',
    Wall = '#',
    Exit = 'E'
};

class Map
{
public:
    Map(const Size& size, int exit_min_distance = 0, int exit_max_distance = std::numeric_limits<int>::max());

    Size size() const;
    Tile tileset(const Point& pos) const;
    Point exitPosition() const;
    const std::vector<std::shared_ptr<Interactable>>& interactables(const Point& pos) const;

    void addInteractable(const Point& pos, std::shared_ptr<Interactable> interactable);
    void removeInteractable(const Point& pos, const Interactable* interactable);

    // Mark the tiles around 'pos' within range 'radius' as visible.
    // Only the tiles marked as visible are rendered.
    void expandVisibility(const Point& pos, int radius);

    void reset();
    void groupSimilarTileset(int threshold);

    bool isMovable(const Point& pos) const;
    bool isVisible(const Point& pos) const;

    std::optional<Path> findPath(const Point& start, const Point& end) const;

private:
    void generateTileset();
    bool trySpawnExit();
    void spawnItems();

    static bool isMovableTileset(Tile tile);

    int m_squared_exit_min_dist;
    int m_squared_exit_max_dist;

    Point m_exit_pos;

    Array2D<Tile> m_tiles;
    Array2D<int> m_visibility;
    Array2D<std::vector<std::shared_ptr<Interactable>>> m_interactables;
};

} // namespace tradungeon

#endif
