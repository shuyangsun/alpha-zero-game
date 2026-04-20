add_library(game_{{cookiecutter.game_slug}} STATIC)

target_link_libraries(
    game_{{cookiecutter.game_slug}}
    PUBLIC
        AlphaZeroAPI::api
{% if cookiecutter.defaults[0] | lower == 'y' -%}
        AlphaZeroAPI::defaults
{%- endif %}
)

target_include_directories(game_{{cookiecutter.game_slug}} PUBLIC ${PROJECT_SOURCE_DIR})

add_subdirectory(game)
