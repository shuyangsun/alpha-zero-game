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
// respresents the presence of a card.
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

  // firt 4 bits = team 0 (players 0 and 2)
  // last 4 bits = team 1 (players 1 and 3)
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
