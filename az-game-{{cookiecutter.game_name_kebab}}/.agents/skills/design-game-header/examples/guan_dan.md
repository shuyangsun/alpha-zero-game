# Guan Dan Game Header Design

The `alpha-zero-api` interface is `IGame<B, A, P>`, so the chosen types must
work with:

- `GetBoard()` returning a compact immutable board object by const reference.
- `ValidActions()` returning a dynamic list of copyable actions.
- `GameAfterAction()` taking one action value and constructing the next state.
- `LastAction()` being able to represent pass as a real action value.
- `CurrentPlayer()`, `LastPlayer()`, and `GetScore()` working for a 4-player
  partnership game rather than a binary-player game.

The framework will keep full action history outside the board for later
serialization, so the board should not duplicate long-term history.

## Final Types

```cpp
namespace az::game::gd {

enum class GdComboType : uint8_t {
  kPass = 0,
  kSingle,
  kPair,
  kTriple,
  kFullHouse,
  kStraight,
  kTube,
  kPlate,
  kStraightFlush,
  kBomb,
  kJokerBomb,
};

// 54 distinct card identities:
// 52 suit-rank cards + small joker + big joker.
// Each identity appears 0, 1, or 2 times because GuanDan uses two decks.
struct GdCardMultiset {
  uint64_t at_least_one = 0;
  uint64_t both_copies = 0;

  bool operator==(const GdCardMultiset&) const = default;
};

struct GdAction {
  GdCardMultiset cards{};           // empty together with kPass means pass
  GdComboType type = GdComboType::kPass;
  uint8_t key_rank = 0;             // raw declared rank; compare with level-aware helpers
};

struct GdBoard {
  std::array<GdCardMultiset, 4> hands{};  // seat order 0,1,2,3

  // Current benchmark for the active trick.
  // Empty + kPass means there is no benchmark and the next player is leading.
  GdAction trick_action{};
  uint8_t trick_player = 0;         // player who set trick_action

  uint8_t current_player = 0;       // player to act next

  // Team levels packed into one byte:
  // low nibble  = team 0 (players 0 and 2)
  // high nibble = team 1 (players 1 and 3)
  uint8_t levels = 0;

  // Four 2-bit finish slots packed into one byte.
  // Slot i stores the player who finished in place i.
  uint8_t finish_order_packed = 0;
  uint8_t num_finished = 0;
};

using GdB = GdBoard;
using GdA = GdAction;
using GdP = uint8_t;  // values 0..3
using GdGameInterface = ::az::game::api::IGame<GdB, GdA, GdP>;

}  // namespace az::game::gd
```

## Why `GdP = uint8_t`

GuanDan has four players, so `BinaryPlayer` is wrong. A plain `uint8_t` keeps
seat rotation, array indexing, and team lookup cheap. A struct of booleans does
not save memory in practice and makes arithmetic and indexing worse. A scoped
enum would also work, but `uint8_t` fits the current API ergonomics better.

## Why `GdCardMultiset`

The core hidden-information object in GuanDan is a two-deck multiset of
specific card identities. The board needs four of them, one per player hand,
and actions need one to say exactly which cards were played.

`GdCardMultiset` uses two 64-bit masks:

- `at_least_one` marks card identities present at least once.
- `both_copies` marks card identities present twice.

This gives a fixed 16-byte representation for any hand fragment, from a single
card up to a 10-card bomb, while still preserving suit and joker identity.
That is much smaller than `std::array<uint8_t, 54>` and avoids the heap and
pointer chasing of `std::vector<CardId>`.

The representation also matches the actual game rule: each of the 54 card
identities can occur 0, 1, or 2 times.

## Why `GdA` Is Not Just `GdCardMultiset`

Using only the raw played cards would be smaller, but it would throw away legal
choice. In GuanDan, especially with heart wild cards, the same physical cards
can often be declared in more than one legal way.

That ambiguity cannot be safely canonicalized away:

- Different declarations can produce different key ranks.
- Different declarations can produce different combo families.
- In a partnership game, a lower declaration can be strategically correct if it
  leaves room for a teammate to win the trick.

Because of that, the action must carry both the exact cards and the player's
declared interpretation of those cards.

`key_rank` stores the raw declared rank. Comparison helpers should interpret it
using the acting team's current level instead of assuming raw numeric order.

Pass is represented directly as an action value:

```cpp
GdAction pass{};
// pass.cards is empty, pass.type == GdComboType::kPass, pass.key_rank == 0
```

That satisfies the API requirement that `LastAction()` still return a concrete
action when the previous player passed.

## Why `GdB` Looks This Way

`GdBoard` carries only state that is needed to generate legal actions, advance
the hand, skip finished players, and score the result.

- `hands` is the dominant cost and contains the actual hidden game state.
- `trick_action` stores the current benchmark declaration to beat.
- `trick_player` identifies who currently owns that benchmark.
- `current_player` identifies who acts next.
- `levels` carries both teams' current level ranks in one byte.
- `finish_order_packed` and `num_finished` track who has already gone out and
  in what order.

The board intentionally does not store:

- full action history, because the framework will own that.
- a permanent passed mask, because pass state is derivable from trick owner,
  current player, and the set of finished seats.
- separate `last_type`, `last_key_rank`, or `last_num_cards`, because those are
  properties of `trick_action`.

On typical 64-bit ABIs this layout is about 96 bytes:

- `4 * GdCardMultiset` for hands: 64 bytes.
- `GdAction trick_action`: 24 bytes.
- five `uint8_t` metadata fields plus alignment padding: about 8 bytes.

That is large enough to be expressive and still compact for MCTS use.

## Packed Helper Accessors

Use shifts and masks rather than compiler bitfields for the packed byte fields.
That keeps layout predictable and easy to reason about.

```cpp
inline uint8_t GdLevelOf(uint8_t levels, uint8_t team) {
  return (levels >> (team * 4)) & 0x0F;
}

inline uint8_t GdFinishAt(uint8_t packed, uint8_t place) {
  return (packed >> (place * 2)) & 0x03;
}
```

## Implications for `include/gd/game.h`

If the generated game slug is `gd`, the type aliases in
`az-game-{{cookiecutter.game_name_kebab}}/include/{{cookiecutter.game_slug}}/game.h`
should resolve to the concrete `gd` types:

```cpp
using GdB = GdBoard;
using GdA = GdAction;
using GdP = uint8_t;
using GdGameInterface = ::az::game::api::IGame<GdB, GdA, GdP>;
```

The important point is not the names themselves. It is that the board owns the
compact in-hand state, the action owns the exact played cards plus declared
meaning, and the player type is a 4-seat integer rather than a binary marker.
