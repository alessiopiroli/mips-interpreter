#include "machine_state.hpp"

#include <stdexcept>
#include <cstring>

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

    for (size_t i = 0; i < gp_registers.size(); ++i) {
        std::cout << register_names[i] << ": 0x" << std::hex << gp_registers[i] << std::endl;
    }

    std::cout << "$pc: 0x" << std::hex << pc << std::endl;
}

uint32_t MachineState::get_register(uint8_t index) const {
    if (index == 0) {
        return 0;
    }

    if (index >= gp_registers.size()) {
        throw std::out_of_range("Register index is out of range");
    }

    return gp_registers[index];
}

void MachineState::set_register(uint8_t index, uint32_t value) {
    if (index == 0) {
        return;
    }

    if (index >= gp_registers.size()) {
        throw std::out_of_range("Register idnex out of range");
    }

    gp_registers[index] = value;
}

uint32_t MachineState::read_word(uint32_t address) const {
    if (address > memory.size() - 4) {
        throw std::out_of_range("Memory read out of bounds");
    }

    uint32_t value;
    std::memcpy(&value, &memory[address], sizeof(value));
    return value;
}

int16_t MachineState::read_half_word_signed(uint32_t address) const {
    if (address > memory.size() - 2) {
        throw std::out_of_range("Memory read out of bounds");
    }

    int16_t value;
    std::memcpy(&value, &memory[address], sizeof(value));
    return value;
}

uint16_t MachineState::read_half_word_unsigned(uint32_t address) const {
    if (address > memory.size() - 2) {
        throw std::out_of_range("Memory read out of bounds");
    }

    uint16_t value;
    std::memcpy(&value, &memory[address], sizeof(value));
    return value;
}

int8_t MachineState::read_byte_signed(uint32_t address) const {
    if (address >= memory.size()) {
        throw std::out_of_range("Memory read out of bounds");
    }

    int8_t value;
    std::memcpy(&value, &memory[address], sizeof(value));
    return value;
}

uint8_t MachineState::read_byte_unsigned(uint32_t address) const {
    if (address >= memory.size()) {
        throw std::out_of_range("Memory read out of bounds");
    }

    uint8_t value;
    std::memcpy(&value, &memory[address], sizeof(value));
    return value;
}

void MachineState::write_word(uint32_t address, uint32_t value) {
    if (address > memory.size() - 4) {
        throw std::out_of_range("Memory write out of bounds");
    }

    std::memcpy(&memory[address], &value, sizeof(value));
}

void MachineState::write_half_word(uint32_t address, uint16_t value) {
    if (address > memory.size() - 2) {
        throw std::out_of_range("Memory write out of bounds");
    }

    std::memcpy(&memory[address], &value, sizeof(value));
}

void MachineState::write_byte(uint32_t address, uint8_t value) {
    if (address >= memory.size()) {
        throw std::out_of_range("Memory write out of bounds");
    }

    std::memcpy(&memory[address], &value, sizeof(value));
}

uint32_t MachineState::get_pc() const {
    return pc;
}

void MachineState::set_pc(uint32_t address) {
    pc = address;
}

void MachineState::set_hi(uint32_t value) {
    hi = value;
}

void MachineState::set_lo(uint32_t value) {
    lo = value;
}

uint32_t MachineState::get_lo() const {
    return lo;
}

uint32_t MachineState::get_hi() const {
    return hi;
}