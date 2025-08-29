#include "gtest/gtest.h"
#include "interpreter.hpp"
#include "machine_state.hpp"
#include "instruction.hpp"

class ShiftReg: public ::testing::Test {
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

TEST_F(ShiftReg, ShiftRegSllv) {
    // sllv $t0, $t1, $t2
    machine->set_register(9, 3); // $t1 = 3
    machine->set_register(10, 5); // $t2 = 5

    // opcode = 000000
    // rs = $t2 = 01010
    // rt = $t1 = 01001
    // rd = $t0 = 01000
    // shamt = 00000
    // funct = 000100
    // Instruction
    // 000000'01010'01001'01000'00000'000100
    // 0000'0001'0100'1001'0100'0000'0000'0100
    // 0x01494004

    Instruction instruction(0x01494004);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_register(8), 96);

}