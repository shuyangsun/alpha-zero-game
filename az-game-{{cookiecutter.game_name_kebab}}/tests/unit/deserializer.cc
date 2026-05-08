#include "gtest/gtest.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

TEST(Deserializer, RejectsWrongSize) {
  GTEST_SKIP() << "TODO(TASK-DESERIALIZER-TEST): verify Deserialize() returns "
                  "an error when the network output has the wrong length.";
}

TEST(Deserializer, ProbabilitiesParallelToActions) {
  GTEST_SKIP() << "TODO(TASK-DESERIALIZER-TEST): verify the returned "
                  "probabilities vector has the same length as the input "
                  "actions span and corresponds 1:1.";
}

TEST(Deserializer, RoundTripsThroughSerializer) {
  GTEST_SKIP() << "TODO(TASK-DESERIALIZER-TEST): verify Deserialize composed "
                  "with Serializer::SerializePolicyOutput recovers the "
                  "original (up to renormalization).";
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
