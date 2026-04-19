import glob
import os
import shutil
import subprocess
import sys

from pathlib import Path


def lower_first_ch(s: str) -> str:
    if not s:
        return s
    return s[0].lower()


has_ci: bool = lower_first_ch("{{ cookiecutter.github_actions }}") == "y"
has_llm: bool = lower_first_ch("{{ cookiecutter.llm }}") == "y"


def remove_ci():
    shutil.rmtree(".github/workflows")


def remove_llm():
    os.remove("AGENTS.md")
    shutil.rmtree("memory/")
    shutil.rmtree("prompts/")
    shutil.rmtree(".agents/")
    shutil.rmtree(".claude/")
    shutil.rmtree(".codex/")
    shutil.rmtree(".gemini/")
    shutil.rmtree(".github/instructions")

    os.remove(".github/copilot-instructions.md")


def symlink_llm():
    root = Path.cwd()
    for name in ("CLAUDE.md", "GEMINI.md"):
        target = root / name
        if target.exists():
            target.unlink()
        try:
            target.symlink_to("AGENTS.md")
        except (OSError, NotImplementedError):
            # Windows without dev-mode/admin: fall back to copy + warn
            shutil.copy(root / "AGENTS.md", target)
            print(
                f"Note: copied {name} (symlinks unavailable on this platform).",
                file=sys.stderr,
            )


if has_llm:
    symlink_llm()
else:
    remove_llm()

if not has_ci and not has_llm:
    shutil.rmtree(".github")

# Format C++ source and header files with clang-format
cpp_files = glob.glob("**/*.h", recursive=True) + glob.glob("**/*.cc", recursive=True)
if cpp_files:
    try:
        subprocess.run(["clang-format", "--style=file", "-i"] + cpp_files, check=True)
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

# Initialize Git repository and make initial commit
_git_env = {**os.environ, "GIT_TERMINAL_PROMPT": "0"}
try:
    subprocess.run(["git", "init"], check=True, capture_output=True, env=_git_env)
    subprocess.run(
        ["git", "branch", "-m", "main"], check=True, capture_output=True, env=_git_env
    )
    subprocess.run(["git", "add", "."], check=True, capture_output=True, env=_git_env)

    # Detect whether GPG/SSH commit signing is enabled
    _gpg_sign = subprocess.run(
        ["git", "config", "--get", "commit.gpgsign"],
        capture_output=True,
        text=True,
        env=_git_env,
    )
    _will_sign = _gpg_sign.returncode == 0 and _gpg_sign.stdout.strip() == "true"

    if _will_sign:
        print(
            "Waiting for initial Git commit signature...",
            flush=True,
        )

    subprocess.run(
        ["git", "commit", "-m", "Initial commit (cookiecutter)"],
        check=True,
        capture_output=True,
        env=_git_env,
    )
except FileNotFoundError:
    print("WARNING: git not found, skipping repository initialization.")
except subprocess.CalledProcessError as e:
    print(f"WARNING: git command failed: {e}", file=sys.stderr)

print()
print("Project generated successfully!")
print()
print("cd ./alpha-zero-game-{{ cookiecutter.game_name_kebab }}")
print("cmake --preset debug && cmake --build --preset debug")
print("./build/debug/{{ cookiecutter.game_slug }} --help")
print()
