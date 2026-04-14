import shutil


def lower_first_ch(s: str) -> str:
    if not s:
        return s
    return s[0].lower()


if lower_first_ch("{{ cookiecutter.github_actions }}") != "y":
    shutil.rmtree(".github")

print()
print("Project generated successfully!")
print()
print("Next steps:")
print()
print("> cd ./alpha-zero-game-{{ cookiecutter.game_name_kebab }}")
print()
print("> cmake -S . -B build -DCMAKE_BUILD_TYPE=Release")
print()
print("> cmake --build build")
print()
print("> ./build/{{ cookiecutter.game_slug }} --help")
print()
