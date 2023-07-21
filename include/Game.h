#ifndef TRADUNGEON_GAME_H
#define TRADUNGEON_GAME_H

#include "Event.h"
#include "TextBuffer.h"
#include "window/WindowManager.h"
#include "scene/Scene.h"
#include <memory>
#include <queue>
#include <any>

namespace tradungeon
{

enum class WindowChange { Push, Pop };

class Game
{
public:
    Game();

    void handleInput(int keycode);
    void update(std::chrono::milliseconds delta_time);
    std::string_view render();

    void handleWindowChanges();

    void loadScene(std::shared_ptr<Scene> scene);

private:
    TextBuffer m_buffer;
    WindowManager m_window_manager;
    std::shared_ptr<Scene> m_scene;

    std::queue<std::pair<WindowChange, std::shared_ptr<Window>>> m_window_changes;
    std::vector<std::any> m_callback_handles;
};

} // namespace tradungeon

#endif
