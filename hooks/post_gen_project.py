import shutil

if "{{ cookiecutter.github_actions }}" != "y":
    shutil.rmtree(".github")

print()
print("Project generated successfully!")
print()
print("Next steps:")
print()
print("> cd ./alpha-zero-game-{{ cookiecutter.game_name_kebab }}")
print()
print(
    "> cmake -S cmake_external_project -B cmake_external_project/build -DCMAKE_BUILD_TYPE=Release"
)
print()
print("> cmake --build cmake_external_project/build")
print()
print(
    "> ./cmake_external_project/build/{{ cookiecutter.__game_name_camel }}/{{ cookiecutter.game_slug }} --help"
)
print()
