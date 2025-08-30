#include "gtest/gtest.h"
#include "interpreter.hpp"
#include "machine_state.hpp"
#include "instruction.hpp"

class TestArithLogic: public ::testing::Test {
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

TEST_F(TestArithLogic, AddPositiveNumbers) {
    machine->set_register(0x08, 2); // $t0 = 2
    machine->set_register(0x09, 3); // $t1 = 3

    // add $t2, $t0, $t1
    // opcode = 000000
    // rs = $t0 = reg. 8 = 01000
    // rt = $t1 = reg. 9 = 01001
    // rd = $t2 = reg. 10 = 01010
    // shamt = 00000
    // funct = 100000
    // INSTRUCTION:
    // 000000'01000'01001'01010'00000'100000
    // 0000'0001'0000'1001'0101'0000'0010'0000
    // 0x01095020
    Instruction instruction(0x01095020);
    interpreter->execute_instruction(instruction);

    ASSERT_EQ(machine->get_register(0x0A), 5);
}

TEST_F(TestArithLogic, AddNegativeNumbers) {
    machine->set_register(0x08, -1); // $t0 = -1
    machine->set_register(0x09, -2); // $t1 = -2

    // add $t2, $t0, $t1
    // opcode = 000000
    // rs = $t0 = reg. 8
    // rt = $t1 = reg. 9
    // shamt = 00000
    // funct = 100000
    // INSTRUCTION
    // 000000'01000'01001'01010'00000'100000
    // 0000'0001'0000'1001'0101'0000'0010'0000
    // 0x01095020

    Instruction instruction(0x01095020);
    interpreter->execute_instruction(instruction);

    ASSERT_EQ(machine->get_register(0x0A), -3);
}

TEST_F(TestArithLogic, AddPosAndNegNumbers) {
    machine->set_register(0x08, 10); // $t0 = 10
    machine->set_register(0x09, -5); // $t1 = -5

    // add $t2, $t0, $t1
    // opcode = 000000
    // rs = $t0 = reg. 8
    // rt = $t1 = reg. 9
    // shamt = 00000
    // funct = 100000
    // INSTRUCTION
    // 000000'01000'01001'01010'00000'100000
    // 0000'0001'0000'1001'0101'0000'0010'0000
    // 0x01095020

    Instruction instruction(0x01095020);
    interpreter->execute_instruction(instruction);

    ASSERT_EQ(machine->get_register(0x0A), 5);
}

TEST_F(TestArithLogic, AddZeroPos) {
    machine->set_register(0x08, 10); // $t0 = 10
    machine->set_register(0x09, 0); // $t1 = 0

    // add $t2, $t0, $t1
    // opcode = 000000
    // rs = $t0 = reg. 8
    // rt = $t1 = reg. 9
    // shamt = 00000
    // funct = 100000
    // INSTRUCTION
    // 000000'01000'01001'01010'00000'100000
    // 0000'0001'0000'1001'0101'0000'0010'0000
    // 0x01095020

    Instruction instruction(0x01095020);
    interpreter->execute_instruction(instruction);

    ASSERT_EQ(machine->get_register(0x0A), 10);
}

TEST_F(TestArithLogic, AddZeroNeg) {
    machine->set_register(0x08, -10); // $t0 = -10
    machine->set_register(0x09, 0); // $t1 = 0

    // add $t2, $t0, $t1
    // opcode = 000000
    // rs = $t0 = reg. 8
    // rt = $t1 = reg. 9
    // shamt = 00000
    // funct = 100000
    // INSTRUCTION
    // 000000'01000'01001'01010'00000'100000
    // 0000'0001'0000'1001'0101'0000'0010'0000
    // 0x01095020

    Instruction instruction(0x01095020);
    interpreter->execute_instruction(instruction);

    ASSERT_EQ(machine->get_register(0x0A), -10);
}