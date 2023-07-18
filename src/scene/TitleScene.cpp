#include "scene/TitleScene.h"
#include "window/TitleMenuWindow.h"
#include "EventMediator.h"

namespace tradungeon
{

void TitleScene::onLoad()
{
    EventMediator::m_on_window_push.signal(std::make_shared<TitleMenuWindow>(Viewport{{0, 0}, {120, 25}}));
}

} // namespace tradungeon
