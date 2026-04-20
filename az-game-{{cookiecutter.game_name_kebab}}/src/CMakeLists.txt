add_subdirectory({{cookiecutter.game_slug}})

add_executable({{ cookiecutter.game_slug }} main.cc)
set_target_properties(
    {{ cookiecutter.game_slug }}
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}"
)
target_include_directories({{ cookiecutter.game_slug }} PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries({{ cookiecutter.game_slug }} PRIVATE game_{{cookiecutter.game_slug}})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(APPLE)
        target_link_options({{ cookiecutter.game_slug }} PRIVATE -Wl,-dead_strip -Wl,-x)
    elseif(UNIX)
        target_link_options({{ cookiecutter.game_slug }} PRIVATE -Wl,--gc-sections -Wl,--discard-all)
    endif()
endif()
