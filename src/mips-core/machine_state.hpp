#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include <cstddef>
#include <iostream>

enum class Registers : uint8_t {
    zero = 0, // $zero
    at = 1, // assembler temporary
    v0, v1, // for return values
    a0, a1, a2, a3, // for arguments
    t0, t1, t2, t3, t4, t5, t6, t7, // temporaries
    s0, s1, s2, s3, s4,s5, s6, s7, // saved
    t8, t9, // temporaries
    k0, k1, // reserved 
    gp, // global pointer
    sp, // stack pointer
    fp, // frame pointer
    ra // return address
};

class MachineState {
private:
    std::vector<uint8_t> memory; // vector for the memory
    std::array<uint32_t, 32> gp_registers; // general purpose registers
    uint32_t pc{}; // program counter
    
    // registers for mult and div
    uint32_t hi{};
    uint32_t lo{};

public:
    explicit MachineState(size_t memory_size); // constructor

    void print_registers(); // function to print registers

    uint32_t get_register(uint8_t index) const; // function to get register
    void set_register(uint8_t index, uint32_t value); // function to set register

    uint32_t read_word(uint32_t address) const;
    uint32_t read_half_word_signed(uint32_t address) const;
    uint32_t read_half_word_unsigned(uint32_t address) const;
    uint32_t read_byte_signed(uint32_t address) const;
    uint32_t read_byte_unsigned(uint32_t address) const;

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