cmake_minimum_required(VERSION 3.26)

project(
    {{ cookiecutter.game_name_camel }}
    VERSION 0.0.1
    LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall -DNDEBUG")

add_executable({{ cookiecutter.game_name_kebab }} src/{{ cookiecutter.game_name_snake }}/main.cc)
