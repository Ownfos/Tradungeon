#include "MapViewer.h"

namespace tradungeon
{

MapViewer::MapViewer(const Viewport& viewport, Map* map, Player* player)
    : UI(viewport), m_map(map), m_player(player)
{}

bool MapViewer::onInput(int keycode)
{
    if (keycode == 'D')
    {
        m_player->m_pos.m_x++;
    }
    if (keycode == 'A')
    {
        m_player->m_pos.m_x--;
    }
    if (keycode == 'W')
    {
        m_player->m_pos.m_y--;
    }
    if (keycode == 'S')
    {
        m_player->m_pos.m_y++;
    }
    if (keycode == 'R')
    {
        m_map->reset();
    }
    if (keycode == 'G')
    {
        m_map->groupSimilarTileset(6);
    }
    return false;
}

void MapViewer::onRender(TextBuffer& buffer)
{
    // The position where player icon should be rendered.
    const auto viewport_center = Point{
        m_viewport.m_size.m_width / 2,
        m_viewport.m_size.m_height / 2
    };

    // Giving distance between map and the UI boundary
    // improves overall visibility by hugh factor!
    constexpr auto horizontals_padding = 4;
    constexpr auto vertical_padding = 2;

    for (int x=horizontals_padding; x<m_viewport.m_size.m_width - horizontals_padding; ++x)
    {
        for (int y=vertical_padding; y<m_viewport.m_size.m_height - vertical_padding; ++y)
        {
            auto viewport_coord = Point{x, y};

            if (viewport_coord == viewport_center)
            {
                // Draw player at the center.
                buffer.renderChar('P', viewport_coord);
            }
            else
            {
                // Convert viewport coordinate to map coordinate.
                // Note that map_coord can go beyond map boundary
                // if viewport is big enough and player is near the edge.
                auto rel_coord = viewport_coord - viewport_center;
                auto map_coord = m_player->position() + rel_coord;

                if (map_coord.isInside(m_map->size()))
                {
                    buffer.renderChar(static_cast<char>(m_map->tileset(map_coord)), viewport_coord);
                }
                else
                {
                    buffer.renderChar(' ', viewport_coord);
                }
            }
        }
    }
}

} // namespace tradungeon
