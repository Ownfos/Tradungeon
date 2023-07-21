#include "Game.h"
#include "EventMediator.h"
#include "scene/TitleScene.h"
#include "Config.h"

namespace tradungeon
{

Game::Game()
    : m_buffer({120, 25})
{
    // Scene loading handler.
    m_callback_handles.push_back(EventMediator::m_on_scene_load.addCallback([&](std::shared_ptr<Scene> scene){
        loadScene(scene);
    }));

    // Window pop/push handlers.
    // These requests are stored in a queue and handled at the very end of a frame.
    m_callback_handles.push_back(EventMediator::m_on_window_push.addCallback([&](std::shared_ptr<Window> window){
        m_window_changes.push({WindowChange::Push, window});
    }));
    m_callback_handles.push_back(EventMediator::m_on_window_pop.addCallback([&](){
        m_window_changes.push({WindowChange::Pop, nullptr});
    }));

    loadScene(std::make_shared<TitleScene>());
}

void Game::handleInput(int keycode)
{
    m_window_manager.handleInput(keycode);
}

void Game::update(std::chrono::milliseconds delta_time)
{
    m_window_manager.update(delta_time);
}

std::string_view Game::render()
{
    m_window_manager.render(m_buffer);

    return m_buffer.getContent();
}

void Game::handleWindowChanges()
{
    while (!m_window_changes.empty())
    {
        auto [type, window] = m_window_changes.front();
        m_window_changes.pop();

        if (type == WindowChange::Pop)
        {
            m_window_manager.pop();
        }
        else
        {
            m_window_manager.push(window);
        }
    }
}

void Game::loadScene(std::shared_ptr<Scene> scene)
{
    m_window_manager.clear();
    scene->onLoad();

    m_scene = scene;
}

} // namespace tradungeon
