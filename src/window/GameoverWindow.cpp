#include "window/GameoverWindow.h"
#include "scene/TitleScene.h"
#include "EventMediator.h"

namespace tradungeon
{

GameoverWindow::GameoverWindow(std::unique_ptr<Statistics>&& statistics, const std::string& ending_description)
    : Window(Viewport{{0, 0}, {120, 25}}),
    m_statistics(std::move(statistics)),
    m_ending_description(ending_description)
{}

bool GameoverWindow::onInput(int keycode)
{
    EventMediator::m_on_scene_load.signal(std::make_shared<TitleScene>());
    return true;
}

void GameoverWindow::onRender(TextBuffer& buffer)
{
    const auto line_area = Size{m_viewport.m_size.m_width, 1};
    renderString(buffer, m_ending_description, Viewport{{0, 4}, line_area}, TextAlign::Center);

    const Clock& time = m_statistics->totalTimeElapsed();
    renderString(buffer, std::format("You survived for {} days {} hours and {} minutes,", time.day(), time.hour(), time.minute()), Viewport{{0, 9}, line_area}, TextAlign::Center);
    renderString(buffer, std::format("traded {} items for total amount of {},", m_statistics->numTradesDone(), m_statistics->netTradeMoney()), Viewport{{0, 10}, line_area}, TextAlign::Center);
    renderString(buffer, std::format("used {} pathfinder's ring,", m_statistics->numExitGuidesUsed()), Viewport{{0, 11}, line_area}, TextAlign::Center);
    renderString(buffer, std::format("walked {} steps,", m_statistics->numStepsWalked()), Viewport{{0, 12}, line_area}, TextAlign::Center);
    renderString(buffer, std::format("ate food {} times,", m_statistics->numFoodEaten()), Viewport{{0, 13}, line_area}, TextAlign::Center);
    renderString(buffer, std::format("and crafted {} items.", m_statistics->numItemsCrafted()), Viewport{{0, 14}, line_area}, TextAlign::Center);

    renderString(buffer, "- press any key to return to the title menu -", Viewport{{0, 20}, line_area}, TextAlign::Center);
}

} // namespace tradungeon
