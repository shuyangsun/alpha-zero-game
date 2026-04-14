cmake_minimum_required(VERSION 3.26)

project(
    {{ cookiecutter.__game_name_camel }}
    VERSION 0.0.1
    LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(ALPHA_ZERO_API_GIT_TAG "main" CACHE STRING "Git tag or branch for AlphaZeroAPI (e.g., main, v1.0.0)")
set(DEFAULTS {% if cookiecutter.defaults[0] | lower == 'y' -%} ON {% else %} OFF {% endif -%} CACHE BOOL "" FORCE)

FetchContent_Declare(
    AlphaZeroAPI
    GIT_REPOSITORY https://github.com/shuyangsun/alpha-zero-api.git
    GIT_TAG "${ALPHA_ZERO_API_GIT_TAG}"
    GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(AlphaZeroAPI)

add_library(game_{{cookiecutter.game_slug}} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/{{ cookiecutter.game_slug }}/game.cc)
target_link_libraries(game_{{cookiecutter.game_slug}} PUBLIC AlphaZeroAPI::api {% if cookiecutter.defaults[0] | lower == 'y' -%}AlphaZeroAPI::defaults{% endif -%})

target_include_directories(game_{{cookiecutter.game_slug}} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable({{ cookiecutter.game_slug }} src/main.cc)
target_include_directories({{ cookiecutter.game_slug }} PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries({{ cookiecutter.game_slug }} PRIVATE AlphaZeroAPI::api)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(APPLE)
        target_link_options({{ cookiecutter.game_slug }} PRIVATE -Wl,-dead_strip -Wl,-x)
    elseif(UNIX)
        target_link_options({{ cookiecutter.game_slug }} PRIVATE -Wl,--gc-sections -Wl,--discard-all)
    endif()
endif()
