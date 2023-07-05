#ifndef TRADUNGEON_GAME_H
#define TRADUNGEON_GAME_H

#include "Event.h"
#include "TextBuffer.h"
#include "window/WindowManager.h"
#include "scene/Scene.h"
#include <memory>
#include <any>

namespace tradungeon
{

class Game
{
public:
    Game();

    void handleInput(int keycode);
    void update(std::chrono::milliseconds delta_time);
    std::string_view render();

    void loadScene(std::shared_ptr<Scene> scene);

private:
    TextBuffer m_buffer;
    WindowManager m_window_manager;
    std::shared_ptr<Scene> m_scene;

    std::vector<std::any> m_callback_handles;
};

} // namespace tradungeon

#endif
