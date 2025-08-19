#include "instruction.hpp"

Instruction::Instruction(uint32_t raw_instruction_) : raw_instruction{raw_instruction_} {}

uint8_t Instruction::opcode() const {
    return ((raw_instruction >> 26) & (0x3F));
}

uint8_t Instruction::rs() const {
    return ((raw_instruction >> 21) & (0x1F));
}

uint8_t Instruction::rt() const {
    return ((raw_instruction >> 16) & (0x1F));
}

uint8_t Instruction::rd() const {
    return ((raw_instruction >> 11) & (0x1F));
}

uint8_t Instruction::shamt() const {
    return ((raw_instruction >> 6) & (0x1F));
}

uint8_t Instruction::funct() const {
    return (raw_instruction & (0x3F));
}

uint16_t Instruction::immediate() const {
    return (raw_instruction & (0xFFFF));
}

uint32_t Instruction::address() const {
    return (raw_instruction & (0x3FFFFFF));
}