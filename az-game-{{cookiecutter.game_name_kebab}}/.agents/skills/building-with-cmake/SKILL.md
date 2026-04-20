---
name: building-with-cmake
description: Build C++ binary and tests with CMake.
---

# Building with CMake

```bash
cmake --preset debug && cmake --build --preset debug
./build/debug/{{cookiecutter.game_slug}}

cmake --preset release && cmake --build --preset release
./build/release/{{cookiecutter.game_slug}}

cmake --preset debug-test && cmake --build --preset debug-test
ctest --preset debug-test

cmake --preset release-test && cmake --build --preset release-test
ctest --preset release-test
```
