#include "Game.h"
#include "EventMediator.h"
#include "interactable/DroppedItem.h"
#include "interactable/DummyItem.h"
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
    // if (keycode == 'L')
    // {
    //     static int next_item_id = 0;
    //     auto bundle = ItemBundle{std::make_shared<DummyItem>("Item #" + std::to_string(next_item_id), next_item_id, 1), 10};
    //     auto dropped_item = std::make_shared<DroppedItem>(bundle);
    //     m_map.addInteractable(m_player.position(), dropped_item);
    //     EventMediator::m_on_item_loot.signal(dropped_item.get());
    //     ++next_item_id;
    // }
    m_window_manager.handleInput(keycode);
}

std::string_view Game::render()
{
    m_window_manager.render(m_buffer);

    return m_buffer.getContent();
}

void Game::loadScene(std::shared_ptr<Scene> scene)
{
    m_scene = scene;

    m_window_manager.clear();
    scene->onLoad();
}

} // namespace tradungeon
