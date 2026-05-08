#include "gtest/gtest.h"

namespace az::game::{{cookiecutter.game_slug}} {
namespace {

TEST(TrainingAugmenter, AugmentReturnsOnePerVariant) {
  GTEST_SKIP() << "TODO(TASK-TRAIN-TEST): verify Augment() returns one tuple "
                  "per supported augmentation.";
}

TEST(TrainingAugmenter, AugmentPermutesPolicyAlongsideBoard) {
  GTEST_SKIP() << "TODO(TASK-TRAIN-TEST): verify the policy probabilities "
                  "are permuted to match the augmented action ordering.";
}

TEST(TrainingAugmenter, AugmentPreservesValue) {
  GTEST_SKIP() << "TODO(TASK-TRAIN-TEST): verify PolicyOutput.value is the "
                  "same in every augmented training tuple.";
}

}  // namespace
}  // namespace az::game::{{cookiecutter.game_slug}}
