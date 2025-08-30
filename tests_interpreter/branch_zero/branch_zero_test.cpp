#include "gtest/gtest.h"
#include "interpreter.hpp"
#include "machine_state.hpp"
#include "instruction.hpp"

class TestBranchZero: public ::testing::Test {
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

TEST_F(TestBranchZero, BranchZeroPosOffsetZeroVal) {
    uint32_t initial_pc = 0;
    machine->set_pc(initial_pc);
    machine->set_register(0x08, 0);
    // machine->set_register(0x09, 10); // $t1 = 10

    // we want to jump forwards 5 instructions
    // 5 instructions = 20 bytes
    // blez $t0, label
    // opcode = 000110
    // rs = reg. 8 = 01000
    // rt = $zero = 00000
    // offset = 5 = 0000'0000'0000'0101
    // INSTRUCTION:
    // 0001'1001'0000'0000'0000'0000'0000'0101
    // 0x19000005

    Instruction instruction(0x19000005);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_pc(), 0x14);
}

TEST_F(TestBranchZero, BranchZeroNegOffsetZeroVal) {
    uint32_t initial_pc = 0x14;
    machine->set_pc(initial_pc);
    machine->set_register(0x08, 0); // $t0 = 10
    // machine->set_register(0x09, 10); // $t1 = 10

    // we want to jump back 5 instructions
    // 5 instructions = 20 bytes
    // blez $t0, label
    // opcode = 000110
    // rs = reg. 8 = 01000
    // rt = $zero = 00000
    // offset = -5 = 1111'1111'1111'1011
    // INSTRUCTION:
    // 0001'1001'0000'0000'1111'1111'1111'1011
    // 0x1900FFFB

    Instruction instruction(0x1900FFFB);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_pc(), 0);
}

TEST_F(TestBranchZero, BranchZeroPosOffsetNegVal) {
    uint32_t initial_pc = 0;
    machine->set_pc(initial_pc);
    machine->set_register(0x08, -10); // $t0 = -10

    // we want to jump forwards 5 instructions
    // 5 instructions = 20 bytes
    // blez $t0, label
    // opcode = 000110
    // rs = reg. 8 = 01000
    // rt = $zero = 00000
    // offset = 5 = 0000'0000'0000'0101
    // INSTRUCTION:
    // 0001'1001'0000'0000'0000'0000'0000'0101
    // 0x19000005

    Instruction instruction(0x19000005);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_pc(), 0x14);
}

TEST_F(TestBranchZero, BranchZeroNegOffsetNegVal) {
    uint32_t initial_pc = 0x14;
    machine->set_pc(initial_pc);
    machine->set_register(0x08, -10); // $t0 = -10

    // we want to jump back 5 instructions
    // 5 instructions = 20 bytes
    // blez $t0, label
    // opcode = 000110
    // rs = reg. 8 = 01000
    // rt = $zero = 00000
    // offset = -5 = 1111'1111'1111'1011
    // INSTRUCTION:
    // 0001'1001'0000'0000'1111'1111'1111'1011
    // 0x1900FFFB

    Instruction instruction(0x1900FFFB);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_pc(), 0);
}

TEST_F(TestBranchZero, BranchZeroNotTaken) {
    uint32_t initial_pc = 0;
    machine->set_pc(initial_pc);
    machine->set_register(0x08, 10); // $t0 = 10

    // we want to jump back 5 instructions if the condition is met
    // 5 instructions = 20 bytes
    // blez $t0, label
    // opcode = 000110
    // rs = reg. 8 = 01000
    // rt = $zero = 00000
    // offset = -5 = 0000'0000'0000'0101
    // INSTRUCTION:
    // 0001'1001'0000'0000'0000'0000'0000'0101
    // 0x19000005

    Instruction instruction(0x19000005);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_pc(), 0);
    ASSERT_NE(machine->get_pc(), 0x14);
}