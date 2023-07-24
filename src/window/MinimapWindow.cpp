#include "window/MinimapWindow.h"
#include "EventMediator.h"

namespace tradungeon
{

MinimapWindow::MinimapWindow(const Viewport& viewport, Map& map, Player& player)
    : Window(viewport), m_map(map), m_player(player)
{}

bool MinimapWindow::onInput(int keycode)
{
    if (keycode == 'Q' || keycode == 'M')
    {
        EventMediator::m_on_window_pop.signal();
    }
    return true;
}

void MinimapWindow::onRender(TextBuffer& buffer)
{
    renderString(buffer, "Minimap", Viewport{{0, 1}, {m_viewport.m_size.m_width, 1}}, TextAlign::Center);

    // Giving distance between map and the Window boundary
    // improves overall visibility by hugh factor!
    //
    // Note: render area refers to the subset of this window's viewport excluding padding,
    //       while viewport refers to the whole area given to this window.
    auto render_area_offset = Point{4, 3};
    auto render_area_size = m_viewport.m_size - Size{render_area_offset.m_x * 2, render_area_offset.m_y * 2};

    // The position inside render area where player should be marked at.
    auto player_render_area_coord = textureCoordinate(render_area_size, m_map.size(), m_player.position());

    for (int x = 0; x < render_area_size.m_width; ++x)
    {
        for (int y = 0; y < render_area_size.m_height; ++y)
        {
            auto render_area_coord = Point{x, y};
            auto viewport_coord = render_area_coord + render_area_offset;

            if (render_area_coord == player_render_area_coord)
            {
                renderChar(buffer, '@', viewport_coord);
            }
            else
            {
                auto map_coord = textureCoordinate(m_map.size(), render_area_size, render_area_coord);
                if (m_map.isVisible(map_coord))
                {
                    renderChar(buffer, static_cast<char>(m_map.tileset(map_coord)), viewport_coord);
                }
                else
                {
                    renderChar(buffer, '?', viewport_coord);
                }
            }
        }
    }
}

Point MinimapWindow::textureCoordinate(const Size& texture_size, const Size& surface_size, const Point& surface_coord)
{
    return {
        (texture_size.m_width - 1) * surface_coord.m_x / (surface_size.m_width - 1),
        (texture_size.m_height - 1) * surface_coord.m_y / (surface_size.m_height - 1)
    };
}

} // namespace tradungeon
