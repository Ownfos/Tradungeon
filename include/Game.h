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

    // Executed window push/pop and scene transition.
    // Delaying these requests guarantees that current frame's
    // input, update, and render are not interrupted.
    void handleWindowAndSceneChanges();

    void loadScene(std::shared_ptr<Scene> scene);

private:
    TextBuffer m_buffer;
    WindowManager m_window_manager;
    std::shared_ptr<Scene> m_scene;

    // These two variables are used to store and delay
    // the execution of Scene/Window change requests.
    std::queue<std::pair<WindowChange, std::shared_ptr<Window>>> m_window_changes;
    std::shared_ptr<Scene> m_next_scene;

    std::vector<std::any> m_callback_handles;
};

} // namespace tradungeon

#endif
