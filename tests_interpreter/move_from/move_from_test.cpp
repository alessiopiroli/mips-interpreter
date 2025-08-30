#include "gtest/gtest.h"
#include "interpreter.hpp"
#include "machine_state.hpp"
#include "instruction.hpp"

class MoveFrom: public ::testing::Test {
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

TEST_F(MoveFrom, MoveFromHi) {
    // mfhi $t0
    uint32_t value_to_move = 0x0F0F0F0F;
    machine->set_hi(value_to_move);

    // opcode = 000000
    // rs = 00000
    // rt = 00000
    // rd = 01000
    // shamt = 00000 
    // funct = 010000
    // Instruction
    // 000000'00000'00000'01000'00000'010000
    // 0000'0000'0000'0000'0100'0000'0001'0000
    // 0x00004010
    
    Instruction instruction(0x00004010);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_register(8), value_to_move);
}