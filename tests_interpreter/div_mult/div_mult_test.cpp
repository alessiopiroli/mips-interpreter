#include "gtest/gtest.h"
#include "interpreter.hpp"
#include "machine_state.hpp"
#include "instruction.hpp"

class DivMult: public ::testing::Test {
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

TEST_F(DivMult, DivNoMod) {
    // 200/40 = 5

    machine->set_register(0x08, 200); // $t0 = 200
    machine->set_register(0x09, 40); // $t1 = 40

    // opcode = 000000
    // rs = $t0 = reg. 8 = 01000
    // rt = $t1 = re.g 9 = 01001
    // rd = 00000
    // shamt = 00000
    // funct = 011010
    // INSTRUCTION:
    // 000000'01000'01001'00000'00000'011010
    // 0000'0001'0000'1001'0000'0000'0001'1010
    // 0x0109001A

    Instruction instruction(0x0109001A);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_lo(), 5);
    ASSERT_EQ(machine->get_hi(), 0);
}

TEST_F(DivMult, DivMod) {
    // 5/2 = 2 (+1)

    machine->set_register(0x08, 5); // $t0 = 5
    machine->set_register(0x09, 2); // $t1 = 2

    // opcode = 000000
    // rs = $t0 = reg. 8 = 01000
    // rt = $t1 = re.g 9 = 01001
    // rd = 00000
    // shamt = 00000
    // funct = 011010
    // INSTRUCTION:
    // 000000'01000'01001'00000'00000'011010
    // 0000'0001'0000'1001'0000'0000'0001'1010
    // 0x0109001A

    Instruction instruction(0x0109001A);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_lo(), 2);
    ASSERT_EQ(machine->get_hi(), 1);
}