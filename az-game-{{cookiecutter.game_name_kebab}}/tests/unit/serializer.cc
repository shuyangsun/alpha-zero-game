#include "gtest/gtest.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

TEST(Serializer, SerializeCurrentStateHasFixedLength) {
  GTEST_SKIP() << "TODO(TASK-SERIALIZER-TEST): verify SerializeCurrentState "
                  "returns the documented fixed length across reachable game "
                  "states.";
}

TEST(Serializer, SerializeCurrentStateEncodesPlayerToMove) {
  GTEST_SKIP() << "TODO(TASK-SERIALIZER-TEST): verify the encoding reflects "
                  "whose turn it is.";
}

TEST(Serializer, SerializePolicyOutputHasFixedLength) {
  GTEST_SKIP() << "TODO(TASK-SERIALIZER-TEST): verify SerializePolicyOutput "
                  "returns the documented fixed length.";
}

TEST(Serializer, SerializePolicyOutputPlacesValueFirst) {
  GTEST_SKIP() << "TODO(TASK-SERIALIZER-TEST): verify result[0] equals "
                  "PolicyOutput.value.";
}

TEST(Serializer, SerializePolicyOutputZeroesInvalidActions) {
  GTEST_SKIP() << "TODO(TASK-SERIALIZER-TEST): verify positions for actions "
                  "outside the input span have zero probability.";
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
