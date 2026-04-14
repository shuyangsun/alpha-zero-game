import glob
import shutil
import subprocess


def lower_first_ch(s: str) -> str:
    if not s:
        return s
    return s[0].lower()


if lower_first_ch("{{ cookiecutter.github_actions }}") != "y":
    shutil.rmtree(".github")

# Format C++ source and header files with clang-format
cpp_files = glob.glob("**/*.h", recursive=True) + glob.glob("**/*.cc", recursive=True)
if cpp_files:
    try:
        subprocess.run(["clang-format", "-i"] + cpp_files, check=True)
    except FileNotFoundError:
        print("WARNING: clang-format not found, skipping C++ formatting.")

# Format CMake files with cmake-format
cmake_files = glob.glob("**/CMakeLists.txt", recursive=True) + glob.glob(
    "**/*.cmake", recursive=True
)
if cmake_files:
    try:
        subprocess.run(["cmake-format", "-i"] + cmake_files, check=True)
    except FileNotFoundError:
        print("WARNING: cmake-format not found, skipping CMake formatting.")

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
