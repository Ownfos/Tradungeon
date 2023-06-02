#ifndef TRADUNGEON_MAP_H
#define TRADUNGEON_MAP_H

#include "Array2D.h"

namespace tradungeon
{

enum class Tile : char
{
    Water = '~',
    Mud = '/',
    Dirt = '-',
    Rock = '#',
    OreVein = '$',
    Lava = '+'
};

class Map
{
public:
    Map(const Size& size);

    void reset();

private:
    Array2D<Tile> m_tiles;
};

} // namespace tradungeon

#endif
