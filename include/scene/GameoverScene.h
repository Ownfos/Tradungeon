#ifndef TRADUNGEON_GAMEOVER_SCENE_H
#define TRADUNGEON_GAMEOVER_SCENE_H

#include "scene/Scene.h"
#include "window/GameoverWindow.h"

namespace tradungeon
{

class GameoverScene : public Scene
{
public:
    GameoverScene(std::unique_ptr<Statistics>&& statistics, const std::string& ending_description);

    virtual void onLoad() override;

private:
    std::shared_ptr<GameoverWindow> m_gameover_window;
};

} // namespace tradungeon

#endif
