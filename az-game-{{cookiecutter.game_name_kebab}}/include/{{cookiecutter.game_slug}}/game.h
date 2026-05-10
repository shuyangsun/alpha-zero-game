#ifndef ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_GAME_H_
#define ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_GAME_H_

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <optional>
#include <string>
#include <string_view>

{% if cookiecutter.defaults[0] | lower == 'y' -%}
#include "alpha-zero-api/defaults/game.h"
{%- endif %}
#include "alpha-zero-api/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

{% if cookiecutter.llm[0] | lower == 'y' -%}
// TODO(TASK-UPDATE-GAME-HEADER): design board type, action type, and player type.
//
// Type aliases below are only placeholders generated from the Cookiecutter template.
//
// Board type: what is intuitive and efficient in memory? Do we need to
// sacrifice runtime efficiency for memory efficiency?
//
// Action type: can we use a small integer type (e.g., uint8_t) to represent all
// possible actions? What's the smallest type we can use here?
//
// Player type: is it a two-player game? Is it a group game? For most two-player
// games, boolean is sufficient.
{%- endif %}
{% if cookiecutter.defaults[0] | lower == 'y' -%}
using {{cookiecutter.__board}} = ::az::game::api::Standard2DBoard<3, 3>;
using {{cookiecutter.__action}} = ::az::game::api::Action2D;
using {{cookiecutter.__player}} = ::az::game::api::BinaryPlayer;
{% else -%}
using {{cookiecutter.__board}} = uint64_t;
using {{cookiecutter.__action}} = int;
using {{cookiecutter.__player}} = bool;
{%- endif %}

/**
 * @brief Error type for {{cookiecutter.__game_cls}} failure.
 */
enum class {{cookiecutter.__game_error}} : uint8_t {
  kUnknownError = 0,
  kNotImplemented,
};

template <typename T>
using {{cookiecutter.__result}} =
    std::expected<T, {{cookiecutter.__game_error}}>;

using {{cookiecutter.__status}} = {{cookiecutter.__result}}<void>;

/**
 * @brief A value-typed implementation of the {{cookiecutter.game_name}} game.
 *
 * Conforms to `::az::game::api::Game`. The MCTS engine is templated on this
 * concrete type, so there is no virtual dispatch and the compiler can see
 * `sizeof({{cookiecutter.__game_cls}})`. Apply transitions in place via
 * `ApplyActionInPlace` and step back via `UndoLastAction`; both are the
 * allocation-free contract used on the MCTS hot path. For cold-path
 * snapshots, prefer the free function
 * `::az::game::api::ApplyAction(game, action)`, which is defined once for
 * any conforming `Game`.
 */
class {{cookiecutter.__game_cls}} {
 public:
  // ----------------------------- Associated types -----------------------------
  using board_t = {{cookiecutter.__board}};
  using action_t = {{cookiecutter.__action}};
  using player_t = {{cookiecutter.__player}};
  using error_t = {{cookiecutter.__game_error}};

  // ------------------------------ Static contract -----------------------------

  /**
   * @brief Number of past states the serializer needs as input.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-UPDATE-GAME-HEADER): set this to the lookback depth required
   * by your network (Markov games keep 0; Atari-style games typically use
   * 4–8).
{%- endif %}
   *
   * Markov games declare 0; the engine still owns the history `RingBuffer`
   * but the view passed to the serializer is always empty.
   */
  static constexpr std::size_t kHistoryLookback = 0;

  /**
   * @brief Cardinality of the full action space — fixed-size policy head.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-UPDATE-GAME-HEADER): set this to the cardinality of your
   * action space, ignoring legality. The bijection between an
   * `{{cookiecutter.__action}}` and a slot in `[0, kPolicySize)` is given
   * by `PolicyIndex`.
{%- endif %}
   */
  {% if cookiecutter.defaults[0] | lower == 'y' -%}
  static constexpr std::size_t kPolicySize = 9;
  {% else -%}
  static constexpr std::size_t kPolicySize = 1;
  {%- endif %}

  /**
   * @brief Per-state upper bound on the number of legal actions
   * `ValidActionsInto` will write.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-UPDATE-GAME-HEADER): set this to the tightest per-state
   * ceiling on legal actions across all reachable states. Must satisfy
   * `kMaxLegalActions <= kPolicySize`. Dense games keep this equal to
   * `kPolicySize`. Switch to a smaller value only if you have decided
   * to use a compact policy head — see the
   * [designing-serialization](../../.agents/skills/designing-serialization/SKILL.md)
   * skill for when that's worth it.
{%- endif %}
   *
   * Also sizes the caller-owned buffer passed to `ValidActionsInto`.
   * Sized against `kPolicySize` for dense heads, or against the
   * legal-action ceiling for compact heads. Changing the layout choice
   * later is a coordinated breaking change across serializer,
   * deserializer, and network output projection.
   */
  {% if cookiecutter.policy_head_layout == 'compact' -%}
  // TODO(policy_head_layout=compact): replace 0 with the tightest
  // per-state legal-action ceiling. Drives the width of the compact
  // policy head.
  static constexpr std::size_t kMaxLegalActions = 0;
  {% else -%}
  static constexpr std::size_t kMaxLegalActions = kPolicySize;
  {%- endif %}

  /**
   * @brief Self-play hard cap on `CurrentRound()`.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-UPDATE-GAME-HEADER): set this to the maximum number of
   * rounds your game can possibly run. Use `std::nullopt` for genuinely
   * unbounded games. The cap exists so pathological loops in
   * early-iteration networks still terminate; if set, `IsOver()` must
   * return `true` once `CurrentRound() >= *kMaxRounds`.
{%- endif %}
   */
  static constexpr std::optional<uint32_t> kMaxRounds = std::nullopt;

  // ------------------------------- Constructors -------------------------------

  /**
   * @brief Construct a fresh {{cookiecutter.game_name}} game state.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-UPDATE-GAME-HEADER): tailor constructors to your game.
   * Decide whether a default constructor is meaningful, whether the
   * starting player needs to be passed in, and whether more constructors
   * are needed.
{%- endif %}
   */
  {{cookiecutter.__game_cls}}() noexcept = default;

  explicit {{cookiecutter.__game_cls}}(
      const {{cookiecutter.__player}}& starting_player) noexcept;

  {{cookiecutter.__game_cls}}(const {{cookiecutter.__game_cls}}& other) noexcept = default;
  {{cookiecutter.__game_cls}}({{cookiecutter.__game_cls}}&& other) noexcept = default;
  {{cookiecutter.__game_cls}}& operator=(const {{cookiecutter.__game_cls}}& other) noexcept = default;
  {{cookiecutter.__game_cls}}& operator=({{cookiecutter.__game_cls}}&& other) noexcept = default;
  ~{{cookiecutter.__game_cls}}() = default;

  // -------------------------------- Observers ---------------------------------

  /**
   * @brief Get the current game board state.
   */
  [[nodiscard]] const {{cookiecutter.__board}}& GetBoard() const noexcept;

  /**
   * @brief Get the current round number.
   */
  [[nodiscard]] uint32_t CurrentRound() const noexcept;

  /**
   * @brief Get the current player.
   */
  [[nodiscard]] {{cookiecutter.__player}} CurrentPlayer() const noexcept;

  /**
   * @brief Get the player from last round, or `std::nullopt` if the game
   * has not started yet.
   */
  [[nodiscard]] std::optional<{{cookiecutter.__player}}> LastPlayer()
      const noexcept;

  /**
   * @brief Get the last action taken, or `std::nullopt` if the game has
   * not started yet.
   */
  [[nodiscard]] std::optional<{{cookiecutter.__action}}> LastAction()
      const noexcept;

  /**
   * @brief Canonical board representation from the current player's
   * perspective.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-HEADER-DOCSTR): tailor this docstring to be
   * {{cookiecutter.game_name}} specific; describe the canonical
   * representation in detail without exceeding a reasonable docstring
   * length.
{%- endif %}
   *
   * For example, for Tic Tac Toe, the canonical form can be a 2D array
   * where the current player's pieces are 1, the opponent's are -1, and
   * empty cells are 0. For incomplete-information games (e.g., card
   * games), the canonical form should only include information visible to
   * the current player.
   *
   * Variations from different perspectives belong in augmenters rather
   * than here. See
   * https://github.com/shuyangsun/alpha-zero-api/blob/main/src/include/alpha-zero-api/augmenter.h
   */
  [[nodiscard]] {{cookiecutter.__board}} CanonicalBoard() const noexcept;

  /**
   * @brief Write the current player's legal actions into `out` and
   * return the count.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-HEADER-DOCSTR): tailor this docstring to be
   * {{cookiecutter.game_name}} specific.
{%- endif %}
   *
   * Writes legal actions into `out[0..count)` and returns `count`.
   * Callers must ignore entries at indices `>= count`. Allocation-free —
   * the buffer is caller-owned and stack-allocated; the same MCTS
   * expansion loop that previously paid for one `std::vector` per call
   * now pays nothing.
   *
   * Must be deterministic in the game state — a training tuple
   * `(s, π, z)` written under one ordering and replayed against a network
   * trained under another is corrupt.
   *
   * No duplicates. Returns `0` if and only if `IsOver()` returns true.
   * While the game is not over, even if there are no "real" choices for
   * the current player, write at least one action (e.g., a "pass")
   * because `ApplyActionInPlace` requires an action.
   */
  [[nodiscard]] std::size_t ValidActionsInto(
      std::array<{{cookiecutter.__action}}, kMaxLegalActions>& out)
      const noexcept;

  /**
   * @brief Whether the game has reached a terminal state.
   *
   * If `kMaxRounds` is set, must return `true` once
   * `CurrentRound() >= *kMaxRounds`. After `IsOver()` is true,
   * `GetScore` is the only method called on this state.
   */
  [[nodiscard]] bool IsOver() const noexcept;

  /**
   * @brief Score for `player` in the current state.
   *
   * Only guaranteed to be meaningful when `IsOver()` is true. Conventional
   * range is `[-1, +1]` from the given player's perspective.
   */
  [[nodiscard]] float GetScore(const {{cookiecutter.__player}}& player)
      const noexcept;

  // ------------------------------ Policy layout -------------------------------

  /**
   * @brief Map an `{{cookiecutter.__action}}` to its slot in the
   * fixed-size policy head.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-HEADER-DOCSTR): describe how the bijection works for
   * {{cookiecutter.game_name}}.
{%- endif %}
   *
   * The returned index must be in `[0, kPolicySize)` and the mapping must
   * be a bijection over the entire action space (legal or not). The
   * default policy serializer/deserializer use this to scatter and gather
   * masked policy values.
   */
  [[nodiscard]] std::size_t PolicyIndex(
      const {{cookiecutter.__action}}& action) const noexcept;

  // -------------------------------- Mutation ----------------------------------

  /**
   * @brief Apply `action` to this state in place.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-HEADER-DOCSTR): tailor this docstring to be
   * {{cookiecutter.game_name}} specific.
{%- endif %}
   *
   * Must be allocation-free — this is the MCTS hot-path primitive. The
   * caller is responsible for passing only actions returned by
   * `ValidActionsInto`; behavior for an invalid action is undefined.
   */
  void ApplyActionInPlace(const {{cookiecutter.__action}}& action) noexcept;

  /**
   * @brief Reverse the most recent `ApplyActionInPlace`.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-HEADER-DOCSTR): tailor this docstring to be
   * {{cookiecutter.game_name}} specific. Make sure your private state
   * (e.g., `action_history_`) supports the depth of undo MCTS will need.
{%- endif %}
   *
   * No-op if there is nothing to undo. Must be allocation-free.
   */
  void UndoLastAction() noexcept;

  // --------------------------- String Conversions ----------------------------

  /**
   * @brief Human-readable string of the current board state.
   *
   * Used in the terminal UI and during debugging. Should be readable by
   * both human and LLM players.
   */
  [[nodiscard]] std::string BoardReadableString() const noexcept;

  /**
   * @brief Parse a human-readable action string.
   */
  [[nodiscard]] {{cookiecutter.__result}}<{{cookiecutter.__action}}>
      ActionFromString(std::string_view action_str) const noexcept;

  /**
   * @brief Format an action as a human-readable string.
   */
  [[nodiscard]] std::string ActionToString(
      const {{cookiecutter.__action}}& action) const noexcept;

 private:
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-UPDATE-GAME-HEADER): design private members to keep track of
  // the game state.
  //
  // The fields below are placeholders. Likely changes:
  //   - `last_action_` / `last_player_` are single-slot; an MCTS rollout
  //     will undo many actions in a row, so you'll usually want a
  //     fixed-size or std::vector-backed action history sized to the
  //     deepest MCTS rollout.
  //   - Some games need richer history (e.g., card-played stack, repeated
  //     position counters). Decide whether to bake those into `board_` or
  //     track them separately.
{%- endif %}
  uint32_t round_ = 0;
  {{cookiecutter.__board}} board_ = {{cookiecutter.__board}}{};
  {{cookiecutter.__player}} cur_player_ = {{cookiecutter.__player}}{};
  std::optional<{{cookiecutter.__action}}> last_action_ = std::nullopt;
  std::optional<{{cookiecutter.__player}}> last_player_ = std::nullopt;
};

static_assert(::az::game::api::Game<{{cookiecutter.__game_cls}}>,
              "{{cookiecutter.__game_cls}} must satisfy ::az::game::api::Game.");

}  // namespace az::game::{{cookiecutter.game_slug}}

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_GAME_H_
