cmake_minimum_required(VERSION 3.26)

project(
    {{ cookiecutter.__game_name_camel }}
    VERSION 0.0.1
    LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall -DNDEBUG")

find_package(AlphaZeroAPI REQUIRED CONFIG)

add_executable({{ cookiecutter.game_slug }} src/main.cc)
target_include_directories({{ cookiecutter.game_slug }} PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries({{ cookiecutter.game_slug }} PRIVATE AlphaZeroAPI::api)
