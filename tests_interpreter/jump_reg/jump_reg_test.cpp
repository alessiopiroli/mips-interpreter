#include "gtest/gtest.h"
#include "interpreter.hpp"
#include "machine_state.hpp"
#include "instruction.hpp"

class JumpReg: public ::testing::Test {
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

TEST_F(JumpReg, JrTest) {
    uint32_t initial_pc = 0;
    machine->set_pc(initial_pc);

    uint32_t target_address = 0x400;
    machine->set_register(8, target_address);

    // jr $t0
    // opcode = 000000
    // funct = 001000
    // rs = $t0 = reg. 8 = 01000
    // rd = rt = 0
    // Instruction:
    // 000000'01000'00000'00000'00000'001000
    // 0000'0001'0000'0000'0000'0000'0000'1000
    // 0x01000008

    Instruction instruction(0x01000008);
    interpreter->execute_instruction(instruction);

    ASSERT_EQ(machine->get_pc(), target_address);
}

TEST_F(JumpReg, JalrTest) {
    uint32_t initial_pc = 0;
    machine->set_pc(initial_pc);

    uint32_t target_address = 0x400;
    machine->set_register(8, target_address);

    // jalr $t0
    // opcode = 000000
    // funct = 001001
    // rs = $t0 = reg. 8 = 01000
    // rd = $ra = reg. 31 = 11111
    // rt = 00000
    // shamt = 00000
    // Instruction:
    // 000000'01000'11111'00000'00000'001001
    // 0000'0001'0001'1111'0000'0000'0000'1001
    // 0x011F0009

    Instruction instruction(0x011F0009);
    machine->set_pc(initial_pc + 4);
    interpreter->execute_instruction(instruction);

    ASSERT_EQ(machine->get_pc(), target_address);
    ASSERT_EQ(machine->get_register(31), initial_pc + 4);
}