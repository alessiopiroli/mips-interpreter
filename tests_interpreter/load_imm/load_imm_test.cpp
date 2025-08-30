#include "gtest/gtest.h"
#include "interpreter.hpp"
#include "machine_state.hpp"
#include "instruction.hpp"

class LoadImm: public ::testing::Test {
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

TEST_F(LoadImm, LloTest) {
    uint32_t initial_value = 0xFFFF0000;
    machine->set_register(8, initial_value);

    // llo $t0 0xEEEE
    // rs = 0
    // rt = $t0
    // opcode = 011000
    // rs = 00000
    // rt = 01000
    // immediate = 0xEEEE = 1110111011101110
    // Instruction:
    // 011000'00000'01000'1110111011101110
    // 0110'0000'0000'1000'1110'1110'1110'1110
    // 0x6008EEEE

    Instruction instruction(0x6008EEEE);
    interpreter->execute_instruction(instruction);

    ASSERT_EQ(machine->get_register(8), 0xFFFFEEEE);
}

TEST_F(LoadImm, LhiTest) {
    uint32_t initial_value = 0x0000FFFF;
    machine->set_register(8, initial_value);

    // lhi $t0 0xEEEE
    // rs = 0
    // rt = $t0
    // opcode = 011001
    // rs = 00000
    // rt = 01000
    // immediate = 0xEEEE = 1110111011101110
    // Instruction:
    // 011001'00000'01000'1110111011101110
    // 0110'0100'0000'1000'1110'1110'1110'1110
    // 0x6408EEEE

    Instruction instruction(0x6408EEEE);
    interpreter->execute_instruction(instruction);

    ASSERT_EQ(machine->get_register(8), 0xEEEEFFFF);
}