#include "machine_state.hpp"

// const array to see register names
static const std::array<const char*, 32> register_names = {
    "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
    "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
    "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
};

MachineState::MachineState(size_t memory_size) : gp_registers{}, pc{} {
    memory.resize(memory_size);
}

void MachineState::print_registers() {
    std::cout << "Registers state:" << std::endl;

    // printing general purpose registers
    for (size_t i = 0; i < gp_registers.size(); ++i) {
        std::cout << register_names[i] << ": 0x" << std::hex << gp_registers[i] << std::endl;
    }

    // printing program counter
    std::cout << "$pc: 0x" << std::hex << pc << std::endl;
}