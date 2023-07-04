add_executable(tradungeon
    main.cpp
    TextBuffer.cpp
    Console.cpp
    Market.cpp
    Tests.cpp
    Random.cpp
    Common.cpp
    ScrollView.cpp
    MessageLog.cpp
    Game.cpp
    Map.cpp
    DiamondSquare.cpp
    PathFinding.cpp
    Player.cpp
    EventMediator.cpp
    Clock.cpp
    Inventory.cpp
    interactable/Item.cpp
    interactable/DroppedItem.cpp
    interactable/DummyItem.cpp
    action/DummyAction.cpp
    action/ItemDropAction.cpp
    action/ItemLootAction.cpp
    window/Window.cpp
    window/WindowManager.cpp
    window/MapWindow.cpp
    window/MessageLogWindow.cpp
    window/InventoryWindow.cpp
    window/ActionListWindow.cpp
    window/InteractableListWindow.cpp
    scene/GameplayScene.cpp
)

target_include_directories(tradungeon PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
