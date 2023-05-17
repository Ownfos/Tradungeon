#ifndef TRADUNGEON_COMMON_H
#define TRADUNGEON_COMMON_H

namespace tradungeon
{

struct Point
{
    int x;
    int y;
};

struct Size
{
    int width;
    int height;
};

struct Viewport
{
    Point offset;
    Size size;
};

} // namespace tradungeon

#endif
