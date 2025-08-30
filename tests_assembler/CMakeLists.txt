cmake_minimum_required(VERSION 3.14)
project(mips-assembler-tests)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(run_assembler_tests
    assembler-test.cpp
    arith_logic/arith_logic_test.cpp
    arith_logic_imm/arith_logic_imm_test.cpp
    branch/branch_test.cpp
    branch_zero/branch_zero_test.cpp
    div_mult/div_mult_test.cpp
    jump/jump_test.cpp
    jump_reg/jump_reg_test.cpp
    load_imm/load_imm_test.cpp
    load_store/load_store_test.cpp
    move_from/move_from_test.cpp
    move_to/move_to_test.cpp
    shift/shift_test.cpp
    shift_reg/shift_reg_test.cpp
    trap/trap_test.cpp
)
target_link_libraries(run_assembler_tests
    PRIVATE
    mips-core
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_assembler_tests)