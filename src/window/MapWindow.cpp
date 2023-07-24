#include "window/MapWindow.h"
#include "window/MinimapWindow.h"
#include "window/InteractableListWindow.h"
#include "window/CraftRecipeListWindow.h"
#include "window/HelpWindow.h"
#include "interactable/DroppedItem.h"
#include "interactable/DummyItem.h"
#include "interactable/UnusableItems.h"
#include "EventMediator.h"
#include "Config.h"
#include <map>

using namespace std::string_literals;
using namespace std::chrono_literals;

namespace tradungeon
{

MapWindow::MapWindow(const Viewport& viewport, Map& map, Player& player, const std::vector<CraftRecipe>& recipes)
    : Window(viewport), m_map(map), m_player(player), m_recipes(recipes),
    m_flicker_tiles(300ms, [this]{ m_highlight_interactables = !m_highlight_interactables; })
{}

void MapWindow::updateNPCPositions(const std::vector<Point>& npc_positions)
{
    m_npc_positions = npc_positions;
}

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
        auto new_pos = m_player.position() + direction[keycode];
        if (new_pos.isInside(m_map.size()) && m_map.isMovable(new_pos))
        {
            m_map.expandVisibility(new_pos, config::map_visibility_radius);
            m_player.move(new_pos);

            if (m_map.tileset(new_pos) == Tile::Water)
            {
                m_player.resetThirst();
            }
            
            return true;
        }
    }
    else if (keycode == 'M')
    {
        auto viewport = Viewport{{20, 5}, {40, 17}};
        EventMediator::m_on_window_push.signal(std::make_shared<MinimapWindow>(viewport, m_map, m_player));
        return true;
    }
    else if (keycode == 'I')
    {
        EventMediator::m_on_inventory_show.signal();
        return true;
    }
    else if (keycode == 'H')
    {
        EventMediator::m_on_window_push.signal(std::make_shared<HelpWindow>());
        return true;
    }
    else if (keycode == 'E')
    {
        const auto& interactables = m_map.interactables(m_player.position());
        auto viewport = Viewport{{20, 10}, {40, 7}};
        EventMediator::m_on_window_push.signal(std::make_shared<InteractableListWindow>(viewport, interactables));
        return true;
    }
    else if (keycode == 'C')
    {
        auto viewport = Viewport{{20, 6}, {40, 10}};
        EventMediator::m_on_window_push.signal(std::make_shared<CraftRecipeListWindow>(viewport, m_recipes, m_player));
        return true;
    }
    // TODO: remove this block when debugging is no longer required
    else if (keycode == 'L')
    {
        static int next_item_id = 0;
        auto bundle = ItemBundle{std::make_shared<DummyItem>("Item #" + std::to_string(next_item_id), next_item_id, 1), 10};
        auto dropped_item = std::make_shared<DroppedItem>(bundle);
        m_map.addInteractable(m_player.position(), dropped_item);
        EventMediator::m_on_item_loot.signal(dropped_item);
        ++next_item_id;
    }
    // TODO: remove this block when debugging is no longer required
    else if (keycode == 'P')
    {
        auto path = m_map.findPath(m_player.position(), m_map.exitPosition()).value();
        EventMediator::m_on_message.signal(std::format("Distance to exit: {}", path.size()));
        return true;
    }
    // TODO: remove this block when debugging is no longer required
    else if (keycode == 'R')
    {
        do
        {
            m_map.reset();
        }
        while (!m_map.isMovable(m_player.position()));
        EventMediator::m_on_message.signal("reset map");
        return true;
    }
    // TODO: remove this block when debugging is no longer required
    else if (keycode == 'G')
    {
        m_map.groupSimilarTileset(6);
        EventMediator::m_on_message.signal("group similar tiles");
        return true;
    }
    // TODO: remove this block when debugging is no longer required
    else if (keycode == 'T')
    {
        EventMediator::m_on_time_elapse.signal(timeunit::hour);
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
    constexpr auto horizontal_padding = 4;
    constexpr auto vertical_padding = 2;

    for (int x=horizontal_padding; x<m_viewport.m_size.m_width - horizontal_padding; ++x)
    {
        for (int y=vertical_padding; y<m_viewport.m_size.m_height - vertical_padding; ++y)
        {
            auto viewport_coord = Point{x, y};
            if (viewport_coord == viewport_center)
            {
                // Draw player at the center.
                renderChar(buffer, '@', viewport_coord);
                continue;
            }

            // Convert viewport coordinate to map coordinate.
            // Note that map_coord can go beyond map boundary
            // if viewport is big enough and player is near the edge.
            auto rel_coord = viewport_coord - viewport_center;
            auto map_coord = m_player.position() + rel_coord;

            // Do not render tiles beyond map boundary.
            if (!map_coord.isInside(m_map.size()))
            {
                renderChar(buffer, ' ', viewport_coord);
                continue;
            }

            // Hide tiles that are not explored yet.
            if (!m_map.isVisible(map_coord))
            {
                renderChar(buffer, '?', viewport_coord);
                continue;
            }

            // Periodically highlight tiles with interactable instances on.
            if (m_highlight_interactables && !m_map.interactables(map_coord).empty())
            {
                renderChar(buffer, '!', viewport_coord);
                continue;
            }

            // Highlight tiles with NPCs on it.
            if (isNPCPlacedOn(map_coord))
            {
                renderChar(buffer, 'N', viewport_coord);
                continue;
            }

            // Otherwise, display the tile type.
            renderChar(buffer, static_cast<char>(m_map.tileset(map_coord)), viewport_coord);
        }
    }
}

void MapWindow::onUpdate(std::chrono::milliseconds delta_time)
{
    m_flicker_tiles.advanceTime(delta_time);
}

bool MapWindow::isNPCPlacedOn(const Point& pos) const
{
    return std::find(m_npc_positions.begin(), m_npc_positions.end(), pos) != m_npc_positions.end();
}

} // namespace tradungeon
