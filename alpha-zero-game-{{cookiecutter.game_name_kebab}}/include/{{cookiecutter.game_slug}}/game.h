#ifndef ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_GAME_H_
#define ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_GAME_H_

#include <expected>
#include <cstdint>
#include <optional>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

{% if cookiecutter.defaults[0] | lower == 'y' -%}
#include "alpha-zero-api/defaults/game.h"
{%- endif %}
#include "alpha-zero-api/game.h"

namespace alphazero::game::{{cookiecutter.game_slug}} {

{% if cookiecutter.defaults[0] | lower == 'y' -%}
using {{cookiecutter.__board}} = ::alphazero::game::api::Standard2DBoard<3, 3>;  // TODO: change type
using {{cookiecutter.__action}} = ::alphazero::game::api::Action2D;               // TODO: change type
using {{cookiecutter.__player}} = ::alphazero::game::api::BinaryPlayer;           // TODO: change type
{% else -%}
using {{cookiecutter.__board}} = uint64_t;  // TODO: change type
using {{cookiecutter.__action}} = int;       // TODO: change type
using {{cookiecutter.__player}} = bool;      // TODO: change type
{%- endif %}
using {{cookiecutter.__game_interface}} = ::alphazero::game::api::IGame<{{cookiecutter.__board}}, {{cookiecutter.__action}}, {{cookiecutter.__player}}>;

class {{cookiecutter.__game_cls}} : public {{cookiecutter.__game_interface}} {
 public:
  {{cookiecutter.__game_cls}}() = default;
  {{cookiecutter.__game_cls}}(const {{cookiecutter.__game_cls}}& other) = default;
  {{cookiecutter.__game_cls}}({{cookiecutter.__game_cls}}&& other) = default;

  ~{{cookiecutter.__game_cls}}() override = default;

  std::unique_ptr<const {{cookiecutter.__game_interface}}> Copy() const final;
  const {{cookiecutter.__board}}& GetBoard() const final;
  uint32_t CurrentRound() const final;
  {{cookiecutter.__player}} CurrentPlayer() const final;
  std::optional<{{cookiecutter.__player}}> LastPlayer() const final;
  std::optional<{{cookiecutter.__action}}> LastAction() const final;
  {{cookiecutter.__board}} CanonicalBoard() const final;
  bool IsOver() const final;
  float GetScore(const {{cookiecutter.__player}}& player) const final;

  // --------------------------------- Actions ---------------------------------

  /**
   * @brief Returns a vector of all valid actions for the current player in the
   * current game state.
{% if cookiecutter.llm[0] | lower == 'y' -%}
   *
   * TODO(TASK-003): tailor this docstring to be {{cookiecutter.game_name}} specific.
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
   * TODO(TASK-003): tailor this docstring to be {{cookiecutter.game_name}} specific.
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

  // String conversions
  std::string BoardReadableString() const final;
  std::expected<{{cookiecutter.__action}}, std::string> ActionFromString(
      std::string_view action_str) const final;
  std::string ActionToString(const {{cookiecutter.__action}}& action) const final;

 private:
  uint32_t round_ = 0;
  {{cookiecutter.__board}} board_ = {{cookiecutter.__board}}{};
  {{cookiecutter.__player}} cur_player_ = {{cookiecutter.__player}}{};
  std::optional<{{cookiecutter.__action}}> last_action_ = std::nullopt;
};

}  // namespace alphazero::game::{{cookiecutter.game_slug}}

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_GAME_H_

