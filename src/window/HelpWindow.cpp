#include "window/HelpWindow.h"
#include "EventMediator.h"

namespace tradungeon
{

HelpWindow::HelpWindow()
    : Window(Viewport{{0, 0}, {120, 25}})
{}

bool HelpWindow::onInput(int keycode)
{
    if (keycode == 'Q')
    {
        EventMediator::m_on_window_pop.signal();
    }
    return true;
}

void HelpWindow::onRender(TextBuffer& buffer)
{
    auto controls =
        "You are trapped in a dungeon and have to find an exit.\n"
        "Move around the map to gather resources and trade with NPCs nearby.\n"
        "You'll need to supply food and water to survive while exploring.\n"
        "The dungeon's terrain transforms periodically, so move quick!\n\n"
        "[Basic in-game controls]\n"
        "- Esc: terminate the game\n"
        "- W, A, S, D: move player\n"
        "- E: open list of interactable entities on player's position\n"
        "- I: open inventory\n"
        "- M: open minimap\n"
        "- C: open crafting menu\n"
        "- H: open this help message\n"
        "- Q: exit / go back\n\n"
        "[When menu window pops up]\n"
        "- E: select item / execute action\n"
        "- W, S: scroll up and down\n";
    auto map_legend =
        "[Map Legend]\n"
        "- '~': water\n"
        "- '/': mud\n"
        "- ' ': dirt\n"
        "- '`': rock\n"
        "- '-': ore vein\n"
        "- '#': wall\n"
        "- '!': interactable instance exists\n"
        "- 'N': tradable NPC\n"
        "- 'E': exit\n";
    renderString(buffer, controls, Viewport{{20, 4}, {80, 20}});
    renderString(buffer, map_legend, Viewport{{90, 9}, {20, 10}});
}

} // namespace tradungeon
