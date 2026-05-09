#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <ostream>
#include <span>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "alpha-zero-api/policy_output.h"
#include "include/{{cookiecutter.game_slug}}/deserializer.h"
#include "include/{{cookiecutter.game_slug}}/game.h"
{% if cookiecutter.augmenter[0] | lower == 'y' -%}
#include "include/{{cookiecutter.game_slug}}/inference.h"
#include "include/{{cookiecutter.game_slug}}/train.h"
{%- endif %}
#include "include/{{cookiecutter.game_slug}}/serializer.h"

namespace {

using ::az::game::api::PolicyOutput;

using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__action}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__board}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__deserializer_cls}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_cls}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_error}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_interface}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_ptr}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__player}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__result}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__serializer_cls}};
{% if cookiecutter.augmenter[0] | lower == 'y' -%}
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__infer_aug_cls}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__train_aug_cls}};

using AugmentedGames =
    std::unordered_map<uint8_t, std::tuple<{{cookiecutter.__board}},
                                           {{cookiecutter.__player}},
                                           std::vector<{{cookiecutter.__action}}>>>;
using TrainingExamples =
    std::vector<std::tuple<{{cookiecutter.__board}}, {{cookiecutter.__player}},
                           std::vector<{{cookiecutter.__action}}>, PolicyOutput>>;
{%- endif %}

constexpr std::string_view kCmdActions = "actions";
constexpr std::string_view kCmdHelp = "help";
constexpr std::string_view kCmdQuit = "quit";

// underlying_type_t<E> may be `uint8_t` (== unsigned char), and operator<<
// on a char type prints a glyph instead of digits. Always promote to
// unsigned for printing.
unsigned ErrorCode({{cookiecutter.__game_error}} e) noexcept {
  return static_cast<unsigned>(
      static_cast<std::underlying_type_t<{{cookiecutter.__game_error}}>>(e));
}

std::string Trim(std::string_view input) noexcept {
  std::size_t start = 0;
  while (start < input.size() &&
         std::isspace(static_cast<unsigned char>(input[start])) != 0) {
    ++start;
  }
  std::size_t end = input.size();
  while (end > start &&
         std::isspace(static_cast<unsigned char>(input[end - 1])) != 0) {
    --end;
  }
  return std::string(input.substr(start, end - start));
}

// Player printing is templated so `if constexpr` discards non-matching
// branches at instantiation time. A non-template function would type-check
// every branch, which breaks for Player types that are neither bool nor
// integral nor stream-printable.
template <typename P>
std::string PlayerString(const P& player) {
  if constexpr (std::is_same_v<P, bool>) {
    return player ? "Player 2" : "Player 1";
  } else if constexpr (std::is_integral_v<P>) {
    std::ostringstream oss;
    oss << "Player " << static_cast<long long>(player);
    return oss.str();
  } else {
    std::ostringstream oss;
    oss << player;
    return oss.str();
  }
}

void PrintHelp(std::ostream& os) {
  os << "Commands:\n"
     << "  <action>   Take an action by typing its string form (the same\n"
     << "             form returned by ActionToString and accepted by\n"
     << "             ActionFromString).\n"
     << "  actions    List the current valid actions.\n"
     << "  help       Show this help message.\n"
     << "  quit       Exit the REPL.\n";
}

void PrintValidActions(std::ostream& os,
                       const {{cookiecutter.__game_interface}}& game,
                       std::span<const {{cookiecutter.__action}}> actions) {
  os << "Valid actions (" << actions.size() << "):\n";
  for (std::size_t i = 0; i < actions.size(); ++i) {
    os << "  " << game.ActionToString(actions[i]) << "\n";
  }
}

bool ApproxEqual(float a, float b) noexcept {
  constexpr float kAbs = 1e-5F;
  constexpr float kRel = 1e-4F;
  const float diff = std::fabs(a - b);
  return diff <= kAbs ||
         diff <= kRel * std::max(std::fabs(a), std::fabs(b));
}

void PrintSerializationDebug(
    std::ostream& os,
    const {{cookiecutter.__game_interface}}& game,
    const {{cookiecutter.__serializer_cls}}& serializer,
    const {{cookiecutter.__deserializer_cls}}& deserializer,
    std::span<const {{cookiecutter.__action}}> actions) {
  const std::vector<float> nn_input = serializer.SerializeCurrentState(
      game.GetBoard(), game.CurrentPlayer(), actions);
  os << "[debug] state vector length:  " << nn_input.size() << "\n";

  std::vector<float> probs(actions.size(), 0.0F);
  if (!actions.empty()) {
    std::fill(probs.begin(), probs.end(),
              1.0F / static_cast<float>(actions.size()));
  }
  const PolicyOutput probe{0.5F, probs};
  const std::vector<float> nn_output = serializer.SerializePolicyOutput(
      game.GetBoard(), game.CurrentPlayer(), actions, probe);
  os << "[debug] policy vector length: " << nn_output.size() << "\n";

  if (nn_output.empty()) {
    os << "[debug] round-trip:           skipped "
       << "(SerializePolicyOutput returned an empty vector)\n";
    return;
  }

  const {{cookiecutter.__result}}<PolicyOutput> roundtrip =
      deserializer.Deserialize(game.GetBoard(), game.CurrentPlayer(), actions,
                               nn_output);
  if (!roundtrip.has_value()) {
    os << "[debug] round-trip:           failed (Deserialize error="
       << ErrorCode(roundtrip.error()) << ")\n";
    return;
  }
  const PolicyOutput& got = *roundtrip;
  bool match = got.probabilities.size() == probe.probabilities.size() &&
               ApproxEqual(got.value, probe.value);
  for (std::size_t i = 0; match && i < probe.probabilities.size(); ++i) {
    if (!ApproxEqual(got.probabilities[i], probe.probabilities[i])) {
      match = false;
    }
  }
  os << "[debug] round-trip:           " << (match ? "match" : "MISMATCH")
     << "\n";
  if (!match) {
    os << "[debug]   probe.value=" << probe.value
       << " got.value=" << got.value << "\n";
    os << "[debug]   probe.probs.size=" << probe.probabilities.size()
       << " got.probs.size=" << got.probabilities.size() << "\n";
  }
}

{% if cookiecutter.augmenter[0] | lower == 'y' -%}
void PrintAugmentationDebug(
    std::ostream& os,
    const {{cookiecutter.__game_interface}}& game,
    const {{cookiecutter.__infer_aug_cls}}& inference,
    const {{cookiecutter.__train_aug_cls}}& trainer,
    std::span<const {{cookiecutter.__action}}> actions) {
  const AugmentedGames augmented = inference.Augment(
      game.GetBoard(), game.CurrentPlayer(), actions);
  os << "[debug] inference variants:   " << augmented.size() << "\n";
  for (const auto& [key, value] : augmented) {
    const std::vector<{{cookiecutter.__action}}>& aug_actions =
        std::get<2>(value);
    os << "[debug]   key=" << static_cast<unsigned>(key)
       << " actions=" << aug_actions.size() << "\n";
  }

  std::vector<float> probs(actions.size(), 0.0F);
  if (!actions.empty()) {
    std::fill(probs.begin(), probs.end(),
              1.0F / static_cast<float>(actions.size()));
  }
  const TrainingExamples training = trainer.Augment(
      game.GetBoard(), game.CurrentPlayer(), actions,
      PolicyOutput{0.0F, probs});
  os << "[debug] training examples:    " << training.size() << "\n";
}
{%- endif %}

// Templated for the same reason PlayerString is: the bool branch calls
// GetScore(true)/GetScore(false), which only type-checks when Player is bool.
template <typename G>
void PrintFinalScores(std::ostream& os, const G& game) {
  using PlayerType = typename G::player_t;
  if constexpr (std::is_same_v<PlayerType, bool>) {
    os << "  " << PlayerString(false) << " score=" << game.GetScore(false)
       << "\n"
       << "  " << PlayerString(true)  << " score=" << game.GetScore(true)
       << "\n";
  } else {
    const PlayerType cur = game.CurrentPlayer();
    os << "  " << PlayerString(cur) << " score=" << game.GetScore(cur)
       << "\n";
    const std::optional<PlayerType> last = game.LastPlayer();
    if (last.has_value()) {
      os << "  " << PlayerString(*last) << " score=" << game.GetScore(*last)
         << "\n";
    }
  }
}

bool FindMatchingValidAction(
    const {{cookiecutter.__game_interface}}& game,
    std::span<const {{cookiecutter.__action}}> actions,
    const {{cookiecutter.__action}}& parsed,
    {{cookiecutter.__action}}* out) {
  const std::string parsed_str = game.ActionToString(parsed);
  for (const {{cookiecutter.__action}}& a : actions) {
    if (game.ActionToString(a) == parsed_str) {
      *out = a;
      return true;
    }
  }
  return false;
}

}  // namespace

int main() {
  std::cout << "=== {{cookiecutter.game_name}} REPL ===\n"
            << "Type \"help\" for commands, \"actions\" to list valid moves, "
            << "\"quit\" to exit.\n";

  {{cookiecutter.__result}}<{{cookiecutter.__game_ptr}}> maybe_game =
      {{cookiecutter.__game_cls}}::Create();
  if (!maybe_game.has_value()) {
    std::cerr << "Error creating game: " << ErrorCode(maybe_game.error())
              << std::endl;
    return 1;
  }
  {{cookiecutter.__game_ptr}} game = std::move(*maybe_game);

  const std::unique_ptr<{{cookiecutter.__serializer_cls}}> serializer =
      std::make_unique<{{cookiecutter.__serializer_cls}}>();
  const std::unique_ptr<{{cookiecutter.__deserializer_cls}}> deserializer =
      std::make_unique<{{cookiecutter.__deserializer_cls}}>();
{% if cookiecutter.augmenter[0] | lower == 'y' -%}
  const std::unique_ptr<{{cookiecutter.__infer_aug_cls}}> inference =
      std::make_unique<{{cookiecutter.__infer_aug_cls}}>();
  const std::unique_ptr<{{cookiecutter.__train_aug_cls}}> trainer =
      std::make_unique<{{cookiecutter.__train_aug_cls}}>();
{%- endif %}

  while (true) {
    std::cout << "\n--- Round " << game->CurrentRound() << " ---\n"
              << "Current: " << PlayerString(game->CurrentPlayer()) << "\n";

    const std::optional<{{cookiecutter.__player}}> last_player =
        game->LastPlayer();
    const std::optional<{{cookiecutter.__action}}> last_action =
        game->LastAction();
    if (last_player.has_value() && last_action.has_value()) {
      std::cout << "Last:    " << PlayerString(*last_player) << " played "
                << game->ActionToString(*last_action) << "\n";
    }
    std::cout << "\n" << game->BoardReadableString() << "\n";

    if (game->IsOver()) {
      std::cout << "\nGame over.\n";
      PrintFinalScores(std::cout, *game);
      return 0;
    }

    const std::vector<{{cookiecutter.__action}}> valid_actions =
        game->ValidActions();
    std::cout << "\nValid actions: " << valid_actions.size()
              << " (type \"actions\" to list)\n";

    PrintSerializationDebug(std::cout, *game, *serializer, *deserializer,
                            valid_actions);
{% if cookiecutter.augmenter[0] | lower == 'y' -%}
    PrintAugmentationDebug(std::cout, *game, *inference, *trainer,
                           valid_actions);
{%- endif %}

    while (true) {
      std::cout << "\n> " << std::flush;
      std::string raw;
      if (!std::getline(std::cin, raw)) {
        std::cout << "\n[EOF — exiting]\n";
        return 0;
      }
      const std::string typed = Trim(raw);
      if (typed.empty()) {
        continue;
      }
      if (typed == kCmdQuit) {
        return 0;
      }
      if (typed == kCmdHelp) {
        PrintHelp(std::cout);
        continue;
      }
      if (typed == kCmdActions) {
        PrintValidActions(std::cout, *game, valid_actions);
        continue;
      }

      const {{cookiecutter.__result}}<{{cookiecutter.__action}}> parsed =
          game->ActionFromString(typed);
      if (!parsed.has_value()) {
        std::cout << "Could not parse \"" << typed << "\" as an action "
                  << "(ActionFromString error=" << ErrorCode(parsed.error())
                  << "). Type \"actions\" to see what is allowed.\n";
        continue;
      }

      {{cookiecutter.__action}} chosen{};
      if (!FindMatchingValidAction(*game, valid_actions, *parsed, &chosen)) {
        std::cout << "\"" << typed
                  << "\" parsed but is not a currently valid action. "
                  << "Type \"actions\" to see what is allowed.\n";
        continue;
      }

      {{cookiecutter.__game_ptr}} next = game->GameAfterAction(chosen);
      if (next == nullptr) {
        std::cerr << "GameAfterAction returned nullptr; cannot continue. "
                  << "If GameAfterAction is still a placeholder, implement it "
                  << "before playing." << std::endl;
        return 1;
      }
      game = std::move(next);
      break;
    }
  }
}
