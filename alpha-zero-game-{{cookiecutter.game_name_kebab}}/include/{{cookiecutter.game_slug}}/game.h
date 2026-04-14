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

  // Actions
  std::vector<{{cookiecutter.__action}}> ValidActions() const final;
  std::unique_ptr<const {{cookiecutter.__game_interface}}> GameAfterAction(
      const {{cookiecutter.__action}}& action) const final;
  bool IsOver() const final;
  float GetScore(const {{cookiecutter.__player}}& player) const final;

  // String conversions
  std::string BoardReadableString() const final;
  std::expected<{{cookiecutter.__action}}, std::string> ActionFromString(
      std::string_view action_str) const final;
  std::string ActionToString(const {{cookiecutter.__action}}& action) const final;

 private:
  uint32_t round_ = 0;
  {{cookiecutter.__board}} board_ = {{cookiecutter.__board}}{};
  {{cookiecutter.__player}} cur_player_;
  std::optional<{{cookiecutter.__action}}> last_action_ = std::nullopt;
};

}  // namespace alphazero::game::{{cookiecutter.game_slug}}

#endif  // ALPHA_ZERO_GAME_{{cookiecutter.__include_guard_prj}}_INCLUDE_{{cookiecutter.__include_guard_slug}}_GAME_H_

