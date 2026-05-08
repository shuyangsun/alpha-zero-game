function(az_add_game_module module_name)
    add_library(${module_name}_{{cookiecutter.game_slug}} STATIC)
    target_link_libraries(
        ${module_name}_{{cookiecutter.game_slug}}
        PUBLIC
            AlphaZeroAPI::api
{% if cookiecutter.defaults[0] | lower == 'y' -%}
            AlphaZeroAPI::defaults
{%- endif %}
            ${ARGN}
    )
    target_include_directories(${module_name}_{{cookiecutter.game_slug}} PUBLIC ${PROJECT_SOURCE_DIR})
endfunction()

az_add_game_module(game)
az_add_game_module(serializer game_{{cookiecutter.game_slug}})
az_add_game_module(deserializer game_{{cookiecutter.game_slug}})
{% if cookiecutter.augmenter[0] | lower == 'y' -%}
az_add_game_module(augmentation game_{{cookiecutter.game_slug}})
az_add_game_module(inference augmentation_{{cookiecutter.game_slug}})
az_add_game_module(train augmentation_{{cookiecutter.game_slug}})
{%- endif %}

add_subdirectory(game)
add_subdirectory(serializer)
add_subdirectory(deserializer)
{% if cookiecutter.augmenter[0] | lower == 'y' -%}
add_subdirectory(augmentation)
add_subdirectory(inference)
add_subdirectory(train)
{%- endif %}
