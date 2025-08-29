#include "gtest/gtest.h"
#include "interpreter.hpp"
#include "machine_state.hpp"
#include "instruction.hpp"

class TestBranch: public ::testing::Test {
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

TEST_F(TestBranch, BranchIsTakenPosOffset) {
    uint32_t initial_pc = 0;
    machine->set_pc(initial_pc);
    machine->set_register(0x08, 10); // $t0 = 10
    machine->set_register(0x09, 10); // $t1 = 10

    // we want to jump forwards 7 instructions
    // 7 instructions = 28 bytes
    // beq $t0, $t1, label
    // opcode = 000100
    // rs = reg. 8 = 01000
    // rt = reg. 9 = 01001
    // offset = 7 = 0000'0000'0000'0111
    // INSTRUCTION:
    // 000100'01000'01001'0000000000000111
    // 0001'0001'0000'1001'0000'0000'0000'0111
    // 0x11090007

    Instruction instruction(0x11090007);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_pc(), 0x1C);
}

TEST_F(TestBranch, BranchIsTakenNegOffset) {
    uint32_t initial_pc = 0x1C;
    machine->set_pc(initial_pc);
    machine->set_register(0x08, 10); // $t0 = 10
    machine->set_register(0x09, 10); // $t1 = 10

    // we want to jump back 7 instructions
    // 7 instructions = 28 bytes
    // beq $t0, $t1, label
    // opcode = 000100
    // rs = reg. 8 = 01000
    // rt = reg. 9 = 01001
    // offset = -7 = 1111'1111'1111'1001
    // INSTRUCTION:
    // 000100'01000'01001'1111111111111001
    // 0001'0001'0000'1001'1111'1111'1111'1001
    // 0x1109FFF9

    Instruction instruction(0x1109FFF9);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_pc(), 0);
}


// ASSERT_NE
TEST_F(TestBranch, BranchNotTaken) {
    uint32_t initial_pc = 0;
    machine->set_pc(initial_pc);
    machine->set_register(0x08, 10); // $t0 = 10
    machine->set_register(0x09, 11); // $t1 = 11

    // we want to jump forward 7 instructions only if the condition is verified
    // 7 instructions = 28 bytes
    // beq $t0, $t1, label
    // opcode = 000100
    // rs = reg. 8 = 01000
    // rt = reg. 9 = 01001
    // offset = 7 = 0000'0000'0000'0111
    // INSTRUCTION:
    // 000100'01000'01001'0000000000000111
    // 0001'0001'0000'1001'0000'0000'0000'0111
    // 0x11090007

    Instruction instruction(0x1109FFF9);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_pc(), 0);
    ASSERT_NE(machine->get_pc(), 0x1C);
}