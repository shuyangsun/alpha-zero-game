# Development Dependencies

## macOS

```bash
curl -LsSf https://astral.sh/uv/install.sh | sh
brew install cmake
brew install clang-format
pip install cmakelang
```

## Linux (Debian/Ubuntu)

```bash
curl -LsSf https://astral.sh/uv/install.sh | sh
sudo apt-get install cmake clang-format
pip install cmake-format
```

## Windows

```powershell
powershell -ExecutionPolicy ByPass -c "irm https://astral.sh/uv/install.ps1 | iex"
winget install Kitware.CMake
winget install LLVM.LLVM        # includes clang-format
pip install cmake-format
```
