add_executable(tradungeon
    main.cpp
    Console.cpp
    Market.cpp
    Tests.cpp
    Random.cpp
    Common.cpp
    UIManager.cpp
    UI.cpp
    MessageLog.cpp
    Game.cpp
)

target_include_directories(tradungeon PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
