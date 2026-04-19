# Guan Dan Game Header Design

## Types

```cpp
#include <array>
#include <cstdint>

namespace az::game::gd {

// Guan Dan player type.
//
// Values 0 through 3.
using GdP = uint8_t;

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
  // Team levels are persistent match levels:
  //   0 -> 2, 1 -> 3, ..., 11 -> K, 12 -> A.
  // Official competitive Guan Dan does not use extra in-play post-A
  // pseudo-levels to count failed attempts. Instead, a team at level A wins
  // the match only by passing A: one player must finish first and the partner
  // must not finish last.
  // A 1-4 finish at level A does not end the match; the team stays at A and
  // must play A again.
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

enum class GdError : uint8_t {
  kUnknownError = 0,
  kNotImplemented,
  kInvalidConstructorArguments,
};

using GdGamePtr = std::unique_ptr<const GdGameInterface>;
using GdGameResult = std::expected<GdGamePtr, TttError>;

class GdGame : public GdGameInterface {
 public:

  [[nodiscard]] static GdGameResult Create(
    // If nullopt, randomly generate a last game finish order.
    // Note that nullopt is different from 0, which represents a fresh game, and
    // player 0 should start the trick.
    std::optional<uint8_t> last_game_finish_order_packed = std::nullopt,
    // If nullopt, random current levels will be generated for both teams.
    // Note that nullopt is different from 0, which represetns a fresh game.
    std::optional<uint8_t> current_team_levels = std::nullopt,
    // If nullopt, a random hand will be delt.
    std::optional<Hands>&& hands = std::nullopt) noexcept;

  // other code...

 private:
  GdGame(
    std::optional<uint8_t> last_game_finish_order_packed,
    std::optional<uint8_t> current_team_levels,
    std::optional<Hands>&& hands) noexcept;

  GdB board_;
  GdP cur_player_;
  uint32_t round_;
};

}  // namespace az::game::gd
```
