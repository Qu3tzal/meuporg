cmake_minimum_required(VERSION 3.5)
project(meuporg-royale-client)

set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 11)

include_directories(source)
include_directories(source/Entity)
include_directories(source/Game)
include_directories(source/Loading)
include_directories(source/Menu)
include_directories(source/RandomNumberGenerator)


include_directories(../../SFML/include)
link_directories(../../SFML/lib)

add_executable(meuporg-royale-client
              source/main.cpp
              source/SFMLPacketUtils.cpp
              source/Entity/Animation.cpp
              source/Entity/Box.cpp
              source/Entity/Bullet.cpp
              source/Entity/Entity.cpp
              source/Entity/EntityWithStats.cpp
              source/Entity/Mission.cpp
              source/Entity/Monster.cpp
              source/Entity/Npc.cpp
              source/Entity/Player.cpp
              source/Entity/Tower.cpp
              source/Game/Game.cpp
              source/Game/Map.cpp
              source/Game/Tile.cpp
              source/Game/TileMap.cpp
              source/Game/World.cpp
              source/Gui/Chat.cpp
              source/Gui/Dialog.cpp
              source/Gui/DialogManager.cpp
              source/Gui/GUIButtonPool.cpp
              source/Gui/GUITextInputPool.cpp
              source/Gui/Hud.cpp
              source/Gui/NameText.cpp
              source/Gui/Statistic.cpp
              source/Loading/Loading.cpp
              source/Menu/Menu.cpp
              source/RandomNumberGenerator/RandomNumberGenerator.cpp
              )
target_link_libraries(meuporg-royale-client sfml-system-d sfml-window-d sfml-graphics-d sfml-network-d sfml-audio-d)
