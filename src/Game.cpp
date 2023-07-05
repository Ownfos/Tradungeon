#include "Game.h"
#include "EventMediator.h"
#include "scene/GameplayScene.h"
#include "Config.h"

namespace tradungeon
{

Game::Game()
    : m_buffer({120, 25})
{
    // Window pop/push handlers.
    m_callback_handles.push_back(EventMediator::m_on_window_push.addCallback([&](std::shared_ptr<Window> window){
        m_window_manager.push(window);
    }));
    
    m_callback_handles.push_back(EventMediator::m_on_window_pop.addCallback([&](){
        m_window_manager.pop();
    }));

    loadScene(std::make_shared<GameplayScene>());
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

void Game::loadScene(std::shared_ptr<Scene> scene)
{
    m_window_manager.clear();
    scene->onLoad();

    m_scene = scene;
}

} // namespace tradungeon
