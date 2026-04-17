add_executable(game_constructors_test game_constructors.cc)
target_link_libraries(game_constructors_test PRIVATE GTest::gtest_main
    game_{{cookiecutter.game_slug}})

include(GoogleTest)
gtest_discover_tests(game_constructors_test)
