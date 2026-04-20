cmake_minimum_required(VERSION 3.26)

project(
    {{ cookiecutter.__game_name_camel }}
    VERSION 0.0.1
    LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(ALPHA_ZERO_API_GIT_TAG
    "v0.0.4"
    CACHE STRING "Git tag or branch for AlphaZeroAPI (e.g., main, v1.0.0)")
set(DEFAULTS {% if cookiecutter.defaults[0] | lower == 'y' -%} ON {% else %} OFF {% endif -%} CACHE BOOL "" FORCE)

FetchContent_Declare(
    AlphaZeroAPI
    GIT_REPOSITORY https://github.com/shuyangsun/alpha-zero-api.git
    GIT_TAG "${ALPHA_ZERO_API_GIT_TAG}"
    GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(AlphaZeroAPI)

option(BUILD_TESTING "Build unit tests" OFF)

add_subdirectory(src)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
