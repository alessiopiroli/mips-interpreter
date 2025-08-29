#include "gtest/gtest.h"
#include "interpreter.hpp"
#include "machine_state.hpp"
#include "instruction.hpp"

class Jump: public ::testing::Test {
protected:
    void SetUp() override {
        machine = new MachineState(1024);
        interpreter = new Interpreter(*machine);
    }

    void TearDown() override {
        delete interpreter;
        delete machine;
    }

    MachineState* machine;
    Interpreter* interpreter;
};

TEST_F(Jump, JumpTest) {
    
}