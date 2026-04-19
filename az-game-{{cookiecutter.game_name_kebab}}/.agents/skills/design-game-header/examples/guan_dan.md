# Guan Dan Game Header Design

## Types

```cpp
#include <array>
#include <cstdint>

namespace az::game::gd {

// Guan Dan player type.
//
// Values 0 through 3.
using GcP = uint8_t;

// 4-bits are enough, no need for 8
enum class ActionType : uint8_t {
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
  kTribute,
  kReturnTribute,
};

// 4-bits are enough, no need for 8
enum class KeyRank : uint8_t {
  kUnknown = 0,
  kAce,
  k2,
  k3,
  k4,
  k5,
  k6,
  k7,
  k8,
  k9,
  k10,
  kJ,
  kQ,
  kK,
  kSmallJoker,
  kBigJoker,
};

// First 4-bits are the underlying value of action type, the last 4-bits are the
// underlying value of key rank.
using PackedTrick = uint8_t;

// Guan Dan action type.
//
// The first 8 bits are PackedTrick, each of the remaining 108 bits
// represents the presence of a card.
// Rank-major representation based on numerical value (A, 2, 3, ..., Big Joker).
// Suits are ordered in clubs, diamonds, hearts, spades.
// The last 15 * 8 - (8 + 108) = 4 bits are 0-padded.
using GdA = std::array<uint8_t, 15>;

// 3 * (54 * 2) = 324 bits total. 3 bits for each card, representing 5 possible
// states - no player holding the card (0b100), or player 0 through 3 holding
// the card (0b000 through 0b011).
// Rank-major representation based on numerical value (A, 2, 3, ..., Big Joker).
// Suits are ordered in clubs, diamonds, hearts, spades.
// The first 54 * 3 = 162 bits are the first deck, the second 162 bits are the
// second deck. The last (41 * 8) - 324 = 4 bits are 0-padded.
using Hands = std::array<uint8_t, 41>;

struct GdBoard {
  Hands hands;

  // First 4 bits = team 0 (players 0 and 2)
  // Last 4 bits = team 1 (players 1 and 3)
  // Levels do not represent the highest-ranked card. For example, at level 0,
  // the highest ranked card is 2.
  // Level 12 is the first time that team is playing with Ace as the
  // highest-ranked card (game point).
  // Level 13 and 14 also represent the highest ranked card being Ace. However,
  // they also encode the number of consecutive losses after reaching game
  // point. Level 13 means they already lost once at game point, and level 14
  // means they already lost twice at game point. At level 14, if they lose
  // again, their team level returns to 0. Note that it has to be three
  // consecutive losses.
  uint8_t team_levels = 0;

  // The current active trick
  PackedTrick active_trick;

  // First 4 bits = player who set active_trick
  // Last 4 bits = number of players finished
  uint8_t trick_player_num_finished_packed;

  // Four 2-bit finish slots packed into one byte.
  // Slot i stores the player who finished in place i.
  uint8_t finish_order_packed = 0;
};

using GdB = GdBoard;

using GdGameInterface = ::az::game::api::IGame<GdB, GdA, GdP>;

// other code...

}  // namespace az::game::gd
```

## Constructor and Private Data Members

```cpp
#include <optional>

namespace az::game::gd {

class GdGame : public GdGameInterface {
 public:
  GdGame(
    Hands&& hands,
    std::optional<uint8_t> last_game_finish_order_packed = std::nullopt,
  );

  // other code...

 private:
  GdB board_;
  GdP cur_player_;
  uint32_t round_;
};

}  // namespace az::game::gd
```
