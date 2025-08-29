cmake_minimum_required(VERSION 3.14)
project(mips-interpreter-tests)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests
    tests-main.cpp
    arith_logic/test_arith_logic.cpp
    arith_logic_imm/test_arith_logic_imm.cpp
    branch/branch_test.cpp
    branch_zero/branch_zero_test.cpp
    div_mult/div_mult_test.cpp
    jump/jump_test.cpp
    jump_reg/jump_reg_test.cpp
)
target_link_libraries(run_tests
    PRIVATE
    mips-core
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)