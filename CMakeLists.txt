cmake_minimum_required(VERSION 3.15)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled1 GBMap.cpp MapLoader.cpp Part2Driver.cpp
        Player.cpp ResourceGather.cpp Resources.cpp VGMaps.cpp VillageScore.cpp GameObserver.cpp)