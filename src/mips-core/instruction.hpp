#pragma once

#include <cstdint>

class Instruction {
private:
    uint32_t raw_instruction;

public:
    Instruction() = default;

    explicit Instruction(uint32_t raw_instruction_);

    uint8_t opcode() const;
    uint8_t rs() const;
    uint8_t rt() const;
    uint8_t rd() const;
    uint8_t shamt() const;
    uint8_t funct() const;
    uint16_t immediate() const;
    uint32_t address() const;
};