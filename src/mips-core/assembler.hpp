#pragma once

#include <unordered_map>
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <sstream>
#include <iomanip>

// NEW
enum class InstructionType {
    R_TYPE,
    I_TYPE,
    J_TYPE,
    TRAP_TYPE
};

// NEW
struct InstructionInfo {
    InstructionType type;
    uint8_t opcode;
    uint8_t funct;

    InstructionInfo(InstructionType type_, uint8_t opcode_, uint8_t funct_);
    InstructionInfo(InstructionType type_, uint8_t opcode_);
};

class Assembler {
private:
    std::unordered_map<std::string, uint32_t> symbol_table;
    std::unordered_map<std::string, uint8_t> register_map; // NEW
    std::unordered_map<std::string, InstructionInfo> instruction_table; // NEW
    std::vector<uint8_t> binary_output;

    void pass1(std::istream& input);
    void pass2(std::istream& input); // NEW

    uint8_t parse_register(std::string token); // NEW
    void parse_mem_operand(std::string token, int16_t& immediate, uint8_t& reg); // NEW

    uint32_t encode_r_type(const InstructionInfo& info, const std::vector<std::string>& operands); // NEW
    uint32_t encode_i_type(const InstructionInfo& info, const std::vector<std::string>& operands, uint32_t current_address); // NEW
    uint32_t encode_j_type(const InstructionInfo& info, const std::vector<std::string>& operands); // NEW
    uint32_t encode_trap_type(const InstructionInfo& info, const std::vector<std::string>& operands); // NEW

    std::vector<uint8_t> run_assembly(std::istream& input);

public:
    Assembler(); // NEW
    void process(std::istream& input, std::ostream& output, bool hex_output);
};