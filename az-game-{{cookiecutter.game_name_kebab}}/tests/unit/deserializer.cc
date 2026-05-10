#include "gtest/gtest.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

TEST(Deserializer, RejectsWrongSize) {
  GTEST_SKIP() << "TODO(TASK-DESERIALIZER-TEST): verify Deserialize() returns "
                  "an error when the network output has the wrong length.";
}

TEST(Deserializer, ProbabilitiesParallelToValidActions) {
  GTEST_SKIP() << "TODO(TASK-DESERIALIZER-TEST): verify the returned "
                  "Evaluation.probabilities vector has the same length as "
                  "the count returned by game.ValidActionsInto(...) and "
                  "corresponds 1:1 to that buffer's first `count` entries.";
}

TEST(Deserializer, RoundTripsThroughSerializer) {
  GTEST_SKIP() << "TODO(TASK-DESERIALIZER-TEST): verify Deserialize composed "
                  "with Serializer::SerializePolicyOutput recovers the "
                  "original value/probabilities (up to renormalization).";
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
