cmake_minimum_required(VERSION 3.26)

project(
    {{ cookiecutter.__game_name_camel }}-SuperBuild
    VERSION 0.0.1
    LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall -DNDEBUG")

include(ExternalProject)

set(ALPHA_ZERO_API_GIT_TAG "main" CACHE STRING "Git tag or branch for AlphaZeroAPI (e.g., main, v1.0.0)")

ExternalProject_Add(
    AlphaZeroAPI
    PREFIX AlphaZeroAPI
    GIT_REPOSITORY https://github.com/shuyangsun/alpha-zero-api.git
    GIT_TAG "${ALPHA_ZERO_API_GIT_TAG}"
    GIT_SHALLOW TRUE
    INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/alpha-zero-api"
    CMAKE_CACHE_ARGS
    -DDEFAULTS:BOOL=ON
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/alpha-zero-api)

ExternalProject_Add(
    {{ cookiecutter.__game_name_camel }}
    PREFIX {{ cookiecutter.__game_name_camel }}
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/.."
    BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/{{ cookiecutter.__game_name_camel }}"
    DEPENDS AlphaZeroAPI
    CMAKE_CACHE_ARGS
    -DCMAKE_PREFIX_PATH:PATH=${CMAKE_CURRENT_BINARY_DIR}/alpha-zero-api
    -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
    INSTALL_COMMAND "")
