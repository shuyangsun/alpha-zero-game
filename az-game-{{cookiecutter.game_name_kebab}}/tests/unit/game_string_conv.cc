#include <memory>
#include <string>
#include <utility>

#include "gtest/gtest.h"
#include "include/{{cookiecutter.game_slug}}/game.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__action}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_cls}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_ptr}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_result}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__player}};

constexpr char kBoardReadableStringNotImplemented[] =
    "\"BoardReadableString()\" is not implemented!";
constexpr char kActionFromStringNotImplemented[] =
    "\"ActionFromString(...)\" is not implemented!";
constexpr char kActionToStringNotImplemented[] =
    "\"ActionToString(...)\" is not implemented!";

[[nodiscard]] {{cookiecutter.__game_ptr}} CreateGame(
    {{cookiecutter.__player}} starting_player = {{cookiecutter.__player}}{}) {
  {{cookiecutter.__game_result}} maybe_game =
      {{cookiecutter.__game_cls}}::Create(starting_player);
  if (!maybe_game.has_value()) {
    ADD_FAILURE() << "Create() returned an error.";
    return nullptr;
  }

  return std::move(*maybe_game);
}

TEST(GameStringConv, BoardReadableStringReturnsPlaceholderMessage) {
  {{cookiecutter.__game_ptr}} game = CreateGame();
  ASSERT_NE(game, nullptr);

  EXPECT_EQ(game->BoardReadableString(), kBoardReadableStringNotImplemented);
}

TEST(GameStringConv, ActionFromStringReturnsPlaceholderError) {
  {{cookiecutter.__game_ptr}} game = CreateGame();
  ASSERT_NE(game, nullptr);

  const std::expected<{{cookiecutter.__action}}, std::string> maybe_action =
      game->ActionFromString("placeholder-action");
  ASSERT_FALSE(maybe_action.has_value());
  EXPECT_EQ(maybe_action.error(), kActionFromStringNotImplemented);
}

TEST(GameStringConv, ActionToStringReturnsPlaceholderMessage) {
  {{cookiecutter.__game_ptr}} game = CreateGame();
  ASSERT_NE(game, nullptr);

  const {{cookiecutter.__action}} action = {{cookiecutter.__action}}{};
  EXPECT_EQ(game->ActionToString(action), kActionToStringNotImplemented);
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
