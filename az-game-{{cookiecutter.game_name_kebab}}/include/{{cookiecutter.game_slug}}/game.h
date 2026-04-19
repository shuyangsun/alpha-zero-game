#ifndef ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_GAME_H_
#define ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_GAME_H_

#include <cstdint>
#include <expected>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

{% if cookiecutter.defaults[0] | lower == 'y' -%}
#include "alpha-zero-api/defaults/game.h"
{%- endif %}
#include "alpha-zero-api/game.h"

namespace az::game::{{cookiecutter.game_slug}} {

{% if cookiecutter.llm[0] | lower == 'y' -%}
// TODO(TASK-004): design board type, action type, and player type.
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
using {{cookiecutter.__game_interface}} = ::az::game::api::IGame<{{cookiecutter.__board}}, {{cookiecutter.__action}}, {{cookiecutter.__player}}>;

/**
 * @brief An implementation of the {{cookiecutter.game_name}} game.
 *
 * All methods on this class are const, the game state is immutable. The only
 * way to create a new game state is to call GameAfterAction() with a valid
 * action, which returns an unique pointer to the new game state.
 */
class {{cookiecutter.__game_cls}} : public {{cookiecutter.__game_interface}} {
 public:

  /**
   * @brief Construct a new {{cookiecutter.game_name}} Game object.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   * 
   * TODO(TASK-004): design constructors, then change the docstring to be {{cookiecutter.game_name}} specific.
   *
   * Does a default constructor make sense? Should we always explicitly pass in
   * the current player to the constructor? Do we need more than one
   * constructor? Delete or add constructor based on your design.
{%- endif %}
   */
  {{cookiecutter.__game_cls}}(const {{cookiecutter.__player}}& player);

  {{cookiecutter.__game_cls}}(const {{cookiecutter.__game_cls}}& other) = default;

  {{cookiecutter.__game_cls}}({{cookiecutter.__game_cls}}&& other) = default;

  ~{{cookiecutter.__game_cls}}() override = default;

  /**
   * @brief Make an identical copy of the current game state.
   *
   * The returned pointer cannot be nullptr, and it points to a new game state
   * that is identical to the current one.
   *
   * @return std::unique_ptr<const {{cookiecutter.__game_interface}}> Unique pointer to the new
   * copy of the game state.
   */
  std::unique_ptr<const {{cookiecutter.__game_interface}}> Copy() const final;

  /**
   * @brief Get the current game board state.
   *
   * @return const {{cookiecutter.__board}}& Const reference to the current game board state.
   */
  const {{cookiecutter.__board}}& GetBoard() const final;

  /**
   * @brief Get the current round number.
   *
   * @return uint32_t The current round number.
   */
  uint32_t CurrentRound() const final;

  /**
   * @brief Get the current player.
   *
   * @return {{cookiecutter.__player}} The current player.
   */
  {{cookiecutter.__player}} CurrentPlayer() const final;

  /**
   * @brief Get the player from last round.
   *
   * @return std::optional<{{cookiecutter.__player}}> The player from last round, or
   * std::nullopt if the game has not started yet.
   */
  std::optional<{{cookiecutter.__player}}> LastPlayer() const final;

  /**
   * @brief Get the last action taken by the last player.
   *
   * @return std::optional<{{cookiecutter.__action}}> The last action taken by the last player,
   * or std::nullopt if the game has not started yet.
   */
  std::optional<{{cookiecutter.__action}}> LastAction() const final;

  /**
   * @brief The canonical representation of the current board state from the
   * current player's perspective.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-005): tailor this docstring to be {{cookiecutter.game_name}} specific, describe the canonical representation in
   * detail, the length should still be suitable for docstring.
{%- endif %}
   *
   * For example, for Tic Tac Toe, the canonical form of the board can be
   * represented as a 2D array where the current player's pieces are marked with
   * 1, the opponent's pieces are marked with -1, and empty cells are marked
   * with 0. For games with incomplete information (e.g., card games), the
   * canonical form should only include information that is visible to the
   * current player.
   *
   * This helps with training machine learning models by providing a consistent
   * representation of the game state from the perspective of the current
   * player during inference time.
   *
   * If variations from different perspectives are desired to increase variance
   * in the training data, that should be handled by augmenters. More details at
   * https://github.com/shuyangsun/alpha-zero-api/blob/main/src/include/alpha-zero-api/augmenter.h
   *
   * @return {{cookiecutter.__board}} The canonical representation of the current board state.
   */
  {{cookiecutter.__board}} CanonicalBoard() const final;

  /**
   * @brief Check if the game is over.
   *
   * If the game is over, no more round can be played by any player. It is safe
   * to call GetScore() after the game is over.
   *
   * @return true If the game is over.
   * @return false If the game is not over.
   */
  bool IsOver() const final;

  /**
   * @brief Get the score of the given player in the current game state.
   *
   * Only guaranteed to return a meaningful score when the game is over. If the
   * game is not over, the returned score may be arbitrary and should not be
   * used for any purpose. The implementation may choose to skip game status
   * check to optimize for performance.
   *
   * @param player The player for which to get the score.
   * @return float The score of the player.
   */
  float GetScore(const {{cookiecutter.__player}}& player) const final;

  // --------------------------------- Actions ---------------------------------

  /**
   * @brief Returns a vector of all valid actions for the current player in the
   * current game state.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-005): tailor this docstring to be {{cookiecutter.game_name}} specific.
{%- endif %}
   *
   * The size of the vector is dynamic, there should be no duplicate actions.
   * This vector should be empty if and only if the game is over. While the game
   * is not over, even if there is no valid action for the current player, the
   * vector should contain at least one action to represent the "pass" action,
   * because the GameAfterAction method requires an action as input.
   *
   * @return std::vector<{{cookiecutter.__action}}> Vector of all valid actions for the current
   * player.
   */
  std::vector<{{cookiecutter.__action}}> ValidActions() const final;

  /**
   * @brief Returns a new game state after the current player takes the given
   * action.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-005): tailor this docstring to be {{cookiecutter.game_name}} specific.
{%- endif %}
   *
   * The action passed in should be only one of the actions returned by the
   * ValidActions() method. The behavior is undefined if the action is invalid.
   * The implementation may choose to return nullptr after checking the validity
   * of the action, or it may return an invalid game state without paying the
   * performance penalty of validation. Most implementations should choose the
   * latter approach, because the library user is responsible for passing a
   * valid action. However, the library user should program defensively and
   * avoid null pointer dereference.
   *
   * @param action The action to be taken by the current player.
   *
   * @return std::unique_ptr<const {{cookiecutter.__game_interface}}> A pointer to the new game
   * state after taking the action.
   */
  std::unique_ptr<const {{cookiecutter.__game_interface}}> GameAfterAction(
      const {{cookiecutter.__action}}& action) const final;

  // --------------------------- String Conversions ----------------------------

  /**
   * @brief Human-readable string to represent the current game state during
   * gameplay in terminal or for debugging.
   *
   * This is the most basic form of user interface for the game, should be easy
   * to understand for both human and LLM players. LLM agents may choose to run
   * the main binary in the terminal to debug game implementation.
   *
   * @return std::string A human-readable string representing the current game
   * state.
   */
  std::string BoardReadableString() const final;

  /**
   * @brief Convert a human-readable string to an action.
   *
   * May be used by a human player or an LLM agent to play the game in the
   * terminal.
   *
   * @param action_str The string representing the action.
   * @return std::expected<{{cookiecutter.__action}}, std::string> The action if the string is
   * valid, or an error message if the string is invalid.
   */
  std::expected<{{cookiecutter.__action}}, std::string> ActionFromString(
      std::string_view action_str) const final;

  /**
   * @brief Convert an action to a human-readable string.
   *
   * Used to display past actions or available actions to human players or LLM
   * agents in the terminal.
   *
   * @param action The action to be converted to string.
   * @return std::string A human-readable string representing the action.
   */
  std::string ActionToString(const {{cookiecutter.__action}}& action) const final;

 private:
{% if cookiecutter.llm[0] | lower == 'y' -%}
  // TODO(TASK-004): design private members to keep track of the game state.
  //
  // `round_`, `cur_player_`, `last_action_`, and `board_`, likely won't change
  // much, but maybe changing them can help.
  //
  // Should we keep track of certain (maybe all) past actions or states that's
  // not fully in the board state? Some game rules may require previous
  // histories. Should they be tracked separately or just baked into the board
  // state?
{%- endif %}
  uint32_t round_ = 0;
  {{cookiecutter.__board}} board_ = {{cookiecutter.__board}}{};
  {{cookiecutter.__player}} cur_player_ = {{cookiecutter.__player}}{};
  std::optional<{{cookiecutter.__action}}> last_action_ = std::nullopt;
};

}  // namespace az::game::{{cookiecutter.game_slug}}

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_GAME_H_

