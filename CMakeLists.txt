cmake_minimum_required(VERSION 3.28)
project(pathfinding_visualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(SFML)

add_executable(sfml_test src/sfml_test.cpp)
target_link_libraries(sfml_test PRIVATE SFML::Graphics)

add_executable(bfs src/bfs.cpp)
target_link_libraries(bfs PRIVATE SFML::Graphics)

add_executable(dfs src/dfs.cpp)
target_link_libraries(dfs PRIVATE SFML::Graphics)

add_executable(dijkstra src/dijkstra.cpp)
target_link_libraries(dijkstra PRIVATE SFML::Graphics)

add_executable(astar src/astar.cpp)
target_link_libraries(astar PRIVATE SFML::Graphics) 
