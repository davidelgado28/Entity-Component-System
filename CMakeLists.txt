cmake_minimum_required(VERSION 3.14)
project(Classic2DGame VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
)
FetchContent_MakeAvailable(SFML)

add_executable(Classic2DGame
    src/main.cpp
)

target_include_directories(Classic2DGame PRIVATE include)
target_link_libraries(Classic2DGame PRIVATE 
    sfml-graphics 
    sfml-window 
    sfml-system
)
