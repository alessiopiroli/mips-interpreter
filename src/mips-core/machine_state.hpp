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

class MachineState{
private:
    std::vector<uint8_t> memory; // vector for the memory
    std::array<uint32_t, 32> gp_registers; // general purpose registers
    uint32_t pc; // program counter

public:
    explicit MachineState(size_t memory_size); // constructor

    void print_registers(); // function to print registers
};