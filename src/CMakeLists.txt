add_executable(tradungeon
    main.cpp
    TextBuffer.cpp
    Console.cpp
    Market.cpp
    MarketSimulator.cpp
    NPCTradeManager.cpp
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
    Clock.cpp
    Inventory.cpp
    Statistics.cpp
    interactable/Item.cpp
    interactable/DroppedItem.cpp
    interactable/DummyItem.cpp
    interactable/UnusableItems.cpp
    interactable/EdibleItems.cpp
    interactable/ExitGuideItem.cpp
    interactable/Exit.cpp
    interactable/NPC.cpp
    action/DummyAction.cpp
    action/ItemDropAction.cpp
    action/ItemLootAction.cpp
    action/ItemEatAction.cpp
    action/ItemTradeAction.cpp
    action/ExitGuideAction.cpp
    action/ExitAction.cpp
    window/Window.cpp
    window/WindowManager.cpp
    window/MapWindow.cpp
    window/MinimapWindow.cpp
    window/MessageLogWindow.cpp
    window/InventoryWindow.cpp
    window/ActionListWindow.cpp
    window/InteractableListWindow.cpp
    window/CraftRecipeListWindow.cpp
    window/CraftRecipeWindow.cpp
    window/StatusWindow.cpp
    window/TitleMenuWindow.cpp
    window/GameoverWindow.cpp
    window/HelpWindow.cpp
    window/GeneratingMapWindow.cpp
    scene/GameplayScene.cpp
    scene/GameoverScene.cpp
    scene/TitleScene.cpp
)

target_include_directories(tradungeon PUBLIC ${CMAKE_SOURCE_DIR}/include)
