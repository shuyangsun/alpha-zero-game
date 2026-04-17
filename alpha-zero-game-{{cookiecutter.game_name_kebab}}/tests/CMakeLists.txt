include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
    GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(googletest)

# Google Test v1.17.0 triggers -Wcharacter-conversion in gtest-printers.h
# (char8_t -> char32_t) under C++23 + Clang. Downgrade the error back to a
# warning for GTest targets so the global -Werror from the preset is bypassed.
# The flag only exists in upstream LLVM Clang (not Apple Clang or GCC), so
# verify support before applying.
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-Wcharacter-conversion _HAS_WCHARACTER_CONVERSION)
if(_HAS_WCHARACTER_CONVERSION)
    foreach(_gt_target gtest gtest_main gmock gmock_main)
        if(TARGET ${_gt_target})
            target_compile_options(${_gt_target} PRIVATE -Wno-error=character-conversion)
        endif()
    endforeach()
endif()

enable_testing()

add_subdirectory(unit)
