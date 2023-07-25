#include "scene/GameoverScene.h"
#include "window/GameoverWindow.h"
#include "EventMediator.h"

namespace tradungeon
{

GameoverScene::GameoverScene(std::unique_ptr<Statistics>&& statistics, const std::string& ending_description)
    : m_gameover_window(std::make_shared<GameoverWindow>(std::move(statistics), ending_description))
{}

void GameoverScene::onLoad()
{
    EventMediator::m_on_window_push.signal(m_gameover_window);
}

} // namespace tradungeon
