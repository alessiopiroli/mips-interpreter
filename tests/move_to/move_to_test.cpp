#include "gtest/gtest.h"
#include "interpreter.hpp"
#include "machine_state.hpp"
#include "instruction.hpp"

class MoveTo: public ::testing::Test {
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

TEST_F(MoveTo, MoveToHi) {
    // mthi $t0
    uint32_t value_to_move = 0x0F0F0F0F;
    machine->set_register(8, value_to_move);

    // opcode = 000000
    // rs = 01000
    // rt = 00000
    // rd = 00000
    // shamt = 00000 
    // funct = 010001
    // Instruction
    // 000000'01000'00000'00000'00000'010001
    // 0000'0001'0000'0000'0000'0000'0001'0001
    // 0x01000011
    
    Instruction instruction(0x01000011);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_hi(), value_to_move);
}