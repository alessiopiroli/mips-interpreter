#include "gtest/gtest.h"
#include "interpreter.hpp"
#include "machine_state.hpp"
#include "instruction.hpp"

class Shift: public ::testing::Test {
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

TEST_F(Shift, ShiftSll) {
    // sll $t0, $t1, 4
    uint32_t initial_value = 5;
    machine->set_register(9, initial_value);

    // opcode = 000000
    // rt = $t1 = reg. 9 = 01001
    // rd = $t0 = reg. 8 = 01000
    // shamt = 4 = 00100 
    // funct = 000000
    // Instruction
    // 000000'00000'01001'01000'00100'000000
    // 0000'0000'0000'1001'0100'0001'0000'0000
    // 0x00094100
    Instruction instruction(0x00094100);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_register(8), 80);
}