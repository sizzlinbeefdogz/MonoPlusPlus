cmake_minimum_required(VERSION 3.8)
project(hoarding)

set(CMAKE_CXX_STANDARD 11)
set(GXX_ENABLE_WARNINGS "-O1 -Wall -Werror -Wno-unused-result")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GXX_ENABLE_WARNINGS}")

set(SOURCE_FILES main.cpp game.cpp game.h rule.cpp rule.h property.cpp property.h board.cpp board.h random.cpp random.h game_state.cpp game_state.h player.cpp player.h move.cpp move.h dice.cpp dice.h)
add_executable(First_HW ${SOURCE_FILES})