---
name: writing-game-header-design-doc
description: Write a design doc outlining the key elements of the game header file.
---

# Writing a game header design document

Design player, action, error, and board types for
[include/{{cookiecutter.game_slug}}/game.h](../../../include/{{cookiecutter.game_slug}}/game.h)
using your best judgment. Do not implement anything; only write the design doc
in [memory/game_design.md](../../../memory/game_design.md).

Ground the design doc in the rules document
[memory/game_rules.md](../../../memory/game_rules.md). Do not make
assumptions that are not clearly stated there. If the rules document is
ambiguous, ask the user to clarify, then update the rules document with that
clarification before proceeding. Although the rule book was written for humans
without much technical background, the design doc should be written as a
technical document for LLMs and software engineers. Include code snippets when
helpful.

## API header template

The {{cookiecutter.game_name}}-specific C++ API header is
[include/{{cookiecutter.game_slug}}/game.h](../../../include/{{cookiecutter.game_slug}}/game.h),
which implements the generic AlphaZero API header. The header may have some
pre-existing type definitions, but they are likely placeholders if there are
TODO comments around them. Use the `finding-alpha-zero-api` skill if the
game-specific API does not provide enough information.

## Key design principles

Optimize for memory efficiency, since these types will be stored in nodes of
the MCTS search tree. Do not worry about serialization or deserialization yet;
that will be
handled by a different interface. Focus on implementing the game logic and
rules correctly while keeping the memory footprint minimal.

## Player

Usually a boolean value for a two-player game, or a `uint8_t` for a game
with more than two players. For some games, you may want a more complex
representation. For example, for werewolf, use the first 7 bits to represent
the player ID, and the last bit to represent whether the player is a werewolf.

## Action

A single action that a player can take given the current game state. Many games
have a "pass" action, which should be explicitly represented by this type,
because an empty vector of valid actions means that the player may be out of the
game, which is different from proactively choosing to pass. You should optimize
this type aggressively for memory footprint, since some games have a very
large action space and the space complexity may grow exponentially. Do not
compact multiple actions into one instance, because each action should produce
a separate game state in the MCTS search tree. If two actions produce
different game states, do not combine them.

## Error

Define an error type to represent invalid actions or game states. Invalid game
states can arise when the arguments to the game constructor are invalid, or when
there is a bug in the game logic implementation. The error states you define
will imply what checks should be implemented in the game logic. Think carefully
about the game logic and what can go wrong when a library user calls the API,
and add `enum class` error values accordingly. Do not worry about having too
many checks that impact performance; most validation will be turned off in
release builds. These checks are mainly for testing and debugging.

## Board

The board type represents most of the game state, so this may be the most
complex type to design. Use an extremely memory-efficient representation for
the general "board" type, because it will be copied for every node in the MCTS
tree. If needed, use a struct and pack information into it as tightly as
possible.

## Length and format

Although these documents are not skills, follow LLM skill best practices when
useful.

Keep the markdown document under 200 lines, with each line under 80 characters.
These documents will be used by LLMs, so keep them concise and avoid wasting
context. Begin each document with a 1-2 sentence summary of the game, followed
by a table of contents under a `## Content` header.

Some designs are too complex to fit under the length limit. In that case, focus
on the core design in the main document and link to separate documents for
details. Create a new directory under [memory](../../../memory/) named
`game_design_details` and store new markdown files there using snake_case.md
filenames, with one file for each specific aspect of the design. These detail
documents do not need a ToC header unless they exceed 100 lines.

Do not nest document references, i.e., `game_design.md` can reference other
documents, but those documents should not reference any other documents. If you
need a detailed document to point elsewhere, either include that content
directly or add the reference to `game_design.md` instead.

## Specific tips for different types of games

**Card games**: see [card_games.md](./card_games.md).
