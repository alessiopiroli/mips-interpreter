#include "gtest/gtest.h"
#include "interpreter.hpp"
#include "machine_state.hpp"
#include "instruction.hpp"

class LoadStore: public ::testing::Test {
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

TEST_F(LoadStore, LoadWord) {
    uint32_t base_address = 0x100;
    int16_t offset = 8;
    uint32_t memory_address = base_address + offset;
    machine->set_register(8, base_address);
    uint32_t value_to_load = 0xABCDEFFF;
    machine->write_word(memory_address, value_to_load);

    // lw $t1, 8($t0)
    // opcode = 100011
    // rs = $t0 = 8 = 01000
    // rt = $t1 = 9 = 01001
    // immediate = 8 = 0000'0000'0000'1000
    // instruction
    // 100011'01000'01001'0000000000001000
    // 1000'1101'0000'1001'0000'0000'0000'1000
    // 0x8D090008

    Instruction instruction(0x8D090008);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->get_register(9), value_to_load);
}

TEST_F(LoadStore, StoreWord) {
    uint32_t base_address = 0x100;
    int16_t offset = 8;
    uint32_t memory_address = base_address + offset;
    machine->set_register(8, base_address);
    uint32_t value_to_load = 0xABCDEFFF;
    machine->set_register(9, value_to_load);

    // sw $t1, 8($t0)
    // opcode = 101011
    // rs = $t0 = 8 = 01000
    // rt = $t1 = 9 = 01001
    // immediate = 8 = 0000'0000'0000'1000
    // instruction
    // 101011'01000'01001'0000000000001000
    // 1010'1101'0000'1001'0000'0000'0000'1000
    // 0xAD090008

    Instruction instruction(0xAD090008);
    interpreter->execute_instruction(instruction);
    ASSERT_EQ(machine->read_word(memory_address), value_to_load);
}