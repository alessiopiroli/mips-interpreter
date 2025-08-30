#include "gtest/gtest.h"
#include "interpreter.hpp"
#include "machine_state.hpp"
#include "instruction.hpp"

class TestArithLogicImm: public ::testing::Test {
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

TEST_F(TestArithLogicImm, AddImmediatePositive) {
    machine->set_register(0x08, 0); // $t0 = 0

    // addi $t0, $zero, 10
    // opcode = 001000
    // rs = $zero = reg. 0 = 00000
    // rd = $t0 = reg. 8 = 01000
    // immediate = 10 = 0000'0000'0000'1010
    // INSTRUCTION:
    // 001000'00000'01000'0000000000001010
    // 0010'0000'0000'1000'0000'0000'0000'1010
    // 0x2008000A
    Instruction instruction(0x2008000A);
    interpreter->execute_instruction(instruction);

    ASSERT_EQ(machine->get_register(0x08), 10);
}

TEST_F(TestArithLogicImm, AddImmediateNegative) {
    machine->set_register(0x08, 0); // $t0 = 0

    // addi $t0, $zero, -10
    // opcode = 001000
    // DA QUI IN POI
    // rs = $zero = reg. 0 = 00000
    // rd = $t0 = reg. 8 = 01000
    // immediate = 10 = 1111'1111'1111'0110
    // INSTRUCTION:
    // 001000'00000'01000'1111111111110110
    // 0010'0000'0000'1000'1111'1111'1111'0110
    // 0x2008FFF6
    Instruction instruction(0x2008FFF6);
    interpreter->execute_instruction(instruction);

    ASSERT_EQ(machine->get_register(0x08), -10);
}

TEST_F(TestArithLogicImm, AddImmediateZero) {
    machine->set_register(0x08, 0); // $t0 = 0

    // addi $t0, $zero, 0
    // opcode = 001000
    // DA QUI IN POI
    // rs = $zero = reg. 0 = 00000
    // rd = $t0 = reg. 8 = 01000
    // immediate = 0 = 0000'0000'0000'0000
    // INSTRUCTION:
    // 001000'00000'01000'0000000000000000
    // 0010'0000'0000'1000'0000'0000'0000'0000
    // 0x20080000
    Instruction instruction(0x20080000);
    interpreter->execute_instruction(instruction);

    ASSERT_EQ(machine->get_register(0x08), 0);
}