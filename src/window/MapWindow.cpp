#include "window/MapWindow.h"
#include "EventMediator.h"
#include "interactable/DummyItem.h"
#include <map>

using namespace std::string_literals;

namespace tradungeon
{

MapWindow::MapWindow(const Viewport& viewport, Map* map, Player* player)
    : Window(viewport), m_map(map), m_player(player)
{}

bool MapWindow::onInput(int keycode)
{
    if ("WASD"s.find(keycode) != std::string::npos)
    {
        auto direction = std::map<char, Point>{
            {'W', {0, -1}},
            {'A', {-1, 0}},
            {'S', {0, 1}},
            {'D', {1, 0}},
        };
        auto new_pos = m_player->position() + direction[keycode];
        if (m_map->isMovable(new_pos))
        {
            EventMediator::m_on_player_move.signal(new_pos);
            return true;
        }
        else
        {
            EventMediator::m_on_message.signal("You cannot move to that tile");
        }
    }
    else if (keycode == 'I')
    {
        EventMediator::m_on_inventory_show.signal();
        return true;
    }
    else if (keycode == 'L')
    {
        static int next_item_id = 0;
        auto bundle = ItemBundle{std::make_shared<DummyItem>("Item #" + std::to_string(next_item_id), next_item_id, 10), 1};
        EventMediator::m_on_item_loot.signal(bundle);
        ++next_item_id;
        return true;
    }
    else if (keycode == 'R')
    {
        m_map->reset();
        EventMediator::m_on_message.signal("reset map");
        return true;
    }
    else if (keycode == 'G')
    {
        m_map->groupSimilarTileset(6);
        EventMediator::m_on_message.signal("group similar tiles");
        return true;
    }
    return false;
}

void MapWindow::onRender(TextBuffer& buffer)
{
    // The position where player icon should be rendered.
    const auto viewport_center = Point{
        m_viewport.m_size.m_width / 2,
        m_viewport.m_size.m_height / 2
    };

    // Giving distance between map and the Window boundary
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
                buffer.renderChar('@', viewport_coord);
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
