#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include <cstddef>
#include <iostream>

enum class Registers : uint8_t {
    zero = 0,
    at = 1,
    v0, v1,
    a0, a1, a2, a3,
    t0, t1, t2, t3, t4, t5, t6, t7,
    s0, s1, s2, s3, s4,s5, s6, s7,
    t8, t9,
    k0, k1,
    gp,
    sp,
    fp,
    ra
};

class MachineState {
private:
    std::vector<uint8_t> memory;
    std::array<uint32_t, 32> gp_registers;
    uint32_t pc{};
    
    uint32_t hi{};
    uint32_t lo{};

public:
    explicit MachineState(size_t memory_size);

    void print_registers();

    uint32_t get_register(uint8_t index) const;
    void set_register(uint8_t index, uint32_t value);

    uint32_t read_word(uint32_t address) const;
    int16_t read_half_word_signed(uint32_t address) const;
    uint16_t read_half_word_unsigned(uint32_t address) const;
    int8_t read_byte_signed(uint32_t address) const;
    uint8_t read_byte_unsigned(uint32_t address) const;

    void write_word(uint32_t address, uint32_t value);
    void write_half_word(uint32_t address, uint16_t value);
    void write_byte(uint32_t address, uint8_t value);

    uint32_t get_pc() const;
    void set_pc(uint32_t address);

    void set_hi(uint32_t value);
    void set_lo(uint32_t value);

    uint32_t get_lo() const;
    uint32_t get_hi() const;
};