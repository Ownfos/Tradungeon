#ifndef TRADUNGEON_MAP_H
#define TRADUNGEON_MAP_H

#include "Array2D.h"

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

    bool isMovable(const Point& pos) const;

    void reset();
    void groupSimilarTileset(int threshold);

private:
    Array2D<Tile> m_tiles;
};

} // namespace tradungeon

#endif
