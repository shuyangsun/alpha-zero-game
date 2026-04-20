---
name: writing-game-header-design-doc
description: Write a design doc outlining key elements of the game header file.
---

# Writing game header design document

Design player, action, error, and board types for
[include/{{cookiecutter.game_slug}}/game.h](../../../include/{{cookiecutter.game_slug}}/game.h)
using your best judgment. Do not implement anything, just write the design doc
in [memory/game_design.md](../../../memory/game_design.md).

Optimize for memory efficiency, as these types will be nodes on the MCTS search
tree. Do not worry about serialization or deserialization yet, that will be
handled by a different interface. Focus on implementing the game logic and rules
correctly, while keeping the memory footprint minimal.

## Player

Usually a boolean value for a binary player game, or an `uint8_t` for a game
with more than two players. For some games, you may want a more complex
representation. For example, for warewolf, use the first 7 bits to represent the
player ID, and use the last bit to represent whether the player is a werewolf or
not.

## Action

A single action a player can take given the current game state. Many games have
a "pass" action, which should be explicitly represented by this type, because
empty vector of valid actions means the player may be out of the game, which is
different from proactively choosing to pass. You should consider extrem memory
footprint optimization for this type, as some games have a very large action
space, the space complexity may grow exponentially. Do not compact multiple
actions into one instance, as each action should result in a separate game state
in the MCTS search tree. If two actions produce different game states, do not
combine them.

## Error

Define an error type to represent any invalid actions or game states. Invalid
game states can arise when arguments to the game construtor are invalid, or when
there is a bug in the game logic implementation. The error states you define
will imply what checks should be implemented in the game logic. Think carefully
about the game logic and what can go wrong when the library user is calling the
API, and add `enum class` error values accordingly. Do not worry about having
too many checks that impacts performances, most of the validation will be turned
off in release builds, they are mainly for testing and debugging purposes.

## Board

The board type represents most of the game state, this may be the most complex
type to design. Use an extremly memory efficient representation for the genral
"board" type, as it will be copied for every single node on the MCTS tree. If
needed, use a struct and pack information into it with the most memory efficient
way.

## Specific tips for different types of games

**Card games**: see [card_games.md](./card_games.md).
