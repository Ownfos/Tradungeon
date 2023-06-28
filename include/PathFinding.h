#ifndef TRADUNGEON_PATH_FINDING_H
#define TRADUNGEON_PATH_FINDING_H

#include "Array2D.h"
#include <optional>
#include <queue>

namespace tradungeon
{

using Path = std::vector<Point>;

std::optional<Path> dijkstra(const Array2D<int>& map, const Point& start, const Point& end);

} // namespace tradungeon

#endif
