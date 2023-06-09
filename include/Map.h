#ifndef TRADUNGEON_MAP_H
#define TRADUNGEON_MAP_H

#include "Array2D.h"
#include "interactable/Interactable.h"

namespace tradungeon
{

enum class Tile : char
{
    Water = '~',
    Mud = '/',
    Dirt = ' ',
    Rock = '`',
    OreVein = '^',
    Lava = 'L',
    Wall = '#',
    Empty = ' '
};

class Map
{
public:
    Map(const Size& size);

    Size size() const;
    Tile tileset(const Point& pos) const;
    const std::vector<std::shared_ptr<Interactable>>& interactables(const Point& pos) const;

    void addInteractable(const Point& pos, std::shared_ptr<Interactable> interactable);
    void removeInteractable(const Point& pos, Interactable* interactable);

    bool isMovable(const Point& pos) const;

    void reset();
    void groupSimilarTileset(int threshold);

private:
    Array2D<Tile> m_tiles;
    Array2D<std::vector<std::shared_ptr<Interactable>>> m_interactables;
};

} // namespace tradungeon

#endif
