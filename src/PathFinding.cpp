#include "PathFinding.h"

namespace tradungeon
{

std::optional<Path> dijkstra(const Array2D<int>& map, const Point& start, const Point& end)
{
    // This should have been a bool array...
    // However, std::vector<bool>::operator[] doesn't give bool&
    // so implementing Array2D<bool>::operator[] was impossible.
    // Instead of making a complicated specialization for Array2D<bool>,
    // I decided to just bypass this issue by using integer 0 and 1.
    auto visited = Array2D<int>(map.size(), 0);
    auto backtrace = Array2D<Point>(map.size());

    auto queue = std::queue<std::pair<Point, Point>>();
    queue.push({start, start});

    while(!queue.empty())
    {
        auto [curr, prev] = queue.front();
        queue.pop();

        // New node is explored.
        if (!visited[curr])
        {
            visited[curr] = 1;
            backtrace[curr] = prev;

            if (curr == end)
            {
                // Reached the destination!
                // Trace the path from end to start.
                auto path = Path();
                while (curr != start)
                {
                    path.push_back(curr);
                    curr = backtrace[curr];
                }

                // Reverse the order to get a path from start to end.
                std::reverse(path.begin(), path.end());

                return path;
            }
            else
            {
                // Keep exploring adjacent nodes.
                const auto neighbors = {
                    curr + Point{1, 0},
                    curr + Point{-1, 0},
                    curr + Point{0, 1},
                    curr + Point{0, -1}
                };
                for (const auto& neighbor : neighbors)
                {
                    if (neighbor.isInside(map.size()) && map[neighbor] && !visited[neighbor])
                    {
                        queue.push({neighbor, curr});
                    }
                }
            }

        }
    }

    // Failed to reach the destination.
    return {};
}

} // namespace tradungeon
