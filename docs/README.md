# AlphaZero Game Template Docs

This docs index maps the AlphaZero Game Template repository for humans and local
RAG retrieval. The template source lives in
`az-game-{{cookiecutter.game_name_kebab}}/`, and generated game repositories get
their implementation guidance from that directory's `memory/` and
`.agents/skills/` files.

## Template Operation

- [Template source map](./template_source_map.md) - where the Cookiecutter
  template stores generated C++ code, memory docs, agent skills, build/test
  wiring, and post-generation behavior.
- [Development dependencies](./dev_dependencies.md) - platform-specific install
  commands for `uv`, CMake, `clang-format`, and `cmake-format`.

## Human-Only Path

- [Old-school human workflow](./old_school_human/README.md) - manual project
  generation, build, and test commands for users who do not use the generated
  LLM agent workflow.
