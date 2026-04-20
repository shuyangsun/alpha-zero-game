---
name: finding-alpha-zero-api
description: Find AlphaZero API header files from GitHub or the local build folder.
---

# Find AlphaZero API Header Files

Header files for this specific {{cookiecutter.game_name}} implementation are in
the[include](../../../include/) directory.

The general AlphaZero API interface header files can be found from <https://github.com/shuyangsun/alpha-zero-api>,
specifically in the `src/include/alpha-zero-api` directory. However, GitHub may
block automated scripts from accessing the repository. In that case, you can
first build the project (use skill `building-with-cmake` if you don't know how),
then look into the `build/debug/_deps/alphazeroapi-src` directory. Header files
are likely in `build/debug/_deps/alphazeroapi-src/src/include/alpha-zero-api`.
When in doubt, search for `augmenter.h` in the build directory.
