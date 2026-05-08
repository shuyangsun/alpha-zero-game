#include <cstdint>
#include <iostream>
#include <memory>
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

using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__deserializer_cls}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_cls}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_error}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__game_ptr}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__result}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__serializer_cls}};
{% if cookiecutter.augmenter[0] | lower == 'y' -%}
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__infer_aug_cls}};
using ::az::game::{{cookiecutter.game_slug}}::{{cookiecutter.__train_aug_cls}};
{%- endif %}

}  // namespace

int main() {
  std::cout << "Hello, {{ cookiecutter.game_name }}!" << std::endl;

  {{cookiecutter.__result}}<{{cookiecutter.__game_ptr}}> maybe_game =
      {{cookiecutter.__game_cls}}::Create();
  if (!maybe_game.has_value()) {
    std::cerr << "Error creating game: "
              << static_cast<std::underlying_type_t<{{cookiecutter.__game_error}}>>(
                     maybe_game.error())
              << std::endl;
    return 1;
  }

  {{cookiecutter.__game_ptr}} game = std::move(*maybe_game);
  std::cout << game->BoardReadableString() << "\n" << std::endl;

  const auto valid_actions = game->ValidActions();
  std::cout << "Number of valid actions: " << valid_actions.size() << std::endl;

  // Serialize current state and a (placeholder) policy output.
  const auto serializer =
      std::make_unique<{{cookiecutter.__serializer_cls}}>();
  const std::vector<float> nn_input = serializer->SerializeCurrentState(
      game->GetBoard(), game->CurrentPlayer(), valid_actions);
  std::cout << "Serialized state vector length: " << nn_input.size()
            << std::endl;

  const PolicyOutput placeholder_policy{
      0.0f, std::vector<float>(valid_actions.size(), 0.0f)};
  const std::vector<float> nn_output = serializer->SerializePolicyOutput(
      game->GetBoard(), game->CurrentPlayer(), valid_actions,
      placeholder_policy);
  std::cout << "Serialized policy output vector length: " << nn_output.size()
            << std::endl;

  // Deserialize the (placeholder) network output back into a PolicyOutput.
  const auto deserializer =
      std::make_unique<{{cookiecutter.__deserializer_cls}}>();
  const auto maybe_policy = deserializer->Deserialize(
      game->GetBoard(), game->CurrentPlayer(), valid_actions, nn_output);
  std::cout << "Deserialization: "
            << (maybe_policy.has_value() ? "ok" : "not implemented yet")
            << std::endl;

{% if cookiecutter.augmenter[0] | lower == 'y' -%}
  // Inference-time augmentation: expand state, run a fake "network" on each
  // variant, then aggregate back into a single PolicyOutput.
  const auto inference =
      std::make_unique<{{cookiecutter.__infer_aug_cls}}>();
  const auto augmented = inference->Augment(
      game->GetBoard(), game->CurrentPlayer(), valid_actions);
  std::cout << "Inference-time augmented variants: " << augmented.size()
            << std::endl;

  std::unordered_map<uint8_t, PolicyOutput> outputs;
  outputs.reserve(augmented.size());
  for (const auto& [key, value] : augmented) {
    const auto& [aug_board, aug_player, aug_actions] = value;
    outputs.emplace(
        key,
        PolicyOutput{0.0f, std::vector<float>(aug_actions.size(), 0.0f)});
  }
  const PolicyOutput interpreted = inference->Interpret(augmented, outputs);
  std::cout << "Interpreted policy probabilities: "
            << interpreted.probabilities.size() << std::endl;

  // Training-time augmentation: expand one (state, policy) example into N
  // equivalent training tuples.
  const auto trainer =
      std::make_unique<{{cookiecutter.__train_aug_cls}}>();
  const auto training_data = trainer->Augment(
      game->GetBoard(), game->CurrentPlayer(), valid_actions,
      PolicyOutput{0.0f, std::vector<float>(valid_actions.size(), 0.0f)});
  std::cout << "Training-time augmented examples: " << training_data.size()
            << std::endl;
{%- endif %}

  return 0;
}
