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

TEST_F(Jump, JTest) {
    uint32_t initial_pc = 0;
    machine->set_pc(initial_pc);

    uint32_t expected_target_address = 0x400;
    // uint32_t word_target_address = expected_target_address / 4;

    // opcode = 000010
    // 0x400/4 = 0x100 = 000100000000
    // 000010 00000000000000 000100000000
    // 0000'1000'0000'0000'0000'0001'0000'0000
    // 0x08000100

    Instruction instruction(0x08000100);
    interpreter->execute_instruction(instruction);

    ASSERT_EQ(machine->get_pc(), expected_target_address);
    ASSERT_EQ(machine->get_register(31), 0);
}