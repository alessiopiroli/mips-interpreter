#include "assembler.hpp"

InstructionInfo::InstructionInfo(InstructionType type_, uint8_t opcode_, uint8_t funct_) :
    type{type_}, opcode{opcode_}, funct{funct_} {}

InstructionInfo::InstructionInfo(InstructionType type_, uint8_t opcode_) :
    type{type_}, opcode{opcode_}, funct{} {}

Assembler::Assembler() {
    // populating the register map
    register_map["$zero"] = 0;
    register_map["$at"] = 1;
    register_map["$v0"] = 2;
    register_map["$v1"] = 3;
    register_map["$a0"] = 4;
    register_map["$a1"] = 5;
    register_map["$a2"] = 6;
    register_map["$a3"] = 7;
    register_map["$t0"] = 8;
    register_map["$t1"] = 9;
    register_map["$t2"] = 10;
    register_map["$t3"] = 11;
    register_map["$t4"] = 12;
    register_map["$t5"] = 13;
    register_map["$t6"] = 14;
    register_map["$t7"] = 15;
    register_map["$s0"] = 16;
    register_map["$s1"] = 17;
    register_map["$s2"] = 18;
    register_map["$s3"] = 19;
    register_map["$s4"] = 20;
    register_map["$s5"] = 21;
    register_map["$s6"] = 22;
    register_map["$s7"] = 23;
    register_map["$t8"] = 24;
    register_map["$t9"] = 25;
    register_map["$k0"] = 26;
    register_map["$k1"] = 27;
    register_map["$gp"] = 28;
    register_map["$sp"] = 29;
    register_map["$s8"] = 30;
    register_map["$ra"] = 31;

    // populating the instruction table
    instruction_table.emplace("sll", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x00});
    instruction_table.emplace("srl", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x02});
    instruction_table.emplace("sra", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x03});
    instruction_table.emplace("sllv", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x04});
    instruction_table.emplace("srlv", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x06});
    instruction_table.emplace("srav", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x07});
    instruction_table.emplace("jr", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x08});
    instruction_table.emplace("jalr", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x09});
    instruction_table.emplace("mfhi", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x10});
    instruction_table.emplace("mthi", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x11});
    instruction_table.emplace("mflo", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x12});
    instruction_table.emplace("mtlo", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x13});
    instruction_table.emplace("mult", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x18});
    instruction_table.emplace("multu", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x19});
    instruction_table.emplace("div", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x1A});
    instruction_table.emplace("divu", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x1B});
    instruction_table.emplace("add", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x20});
    instruction_table.emplace("addu", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x21});
    instruction_table.emplace("sub", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x22});
    instruction_table.emplace("subu", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x23});
    instruction_table.emplace("and", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x24});
    instruction_table.emplace("or", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x25});
    instruction_table.emplace("xor", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x26});
    instruction_table.emplace("nor", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x27});
    instruction_table.emplace("slt", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x2A});
    instruction_table.emplace("sltu", InstructionInfo{InstructionType::R_TYPE, 0x00, 0x2B});

    instruction_table.emplace("beq", InstructionInfo{InstructionType::I_TYPE, 0x04});
    instruction_table.emplace("bne", InstructionInfo{InstructionType::I_TYPE, 0x05});
    instruction_table.emplace("blez", InstructionInfo{InstructionType::I_TYPE, 0x06});
    instruction_table.emplace("bgtz", InstructionInfo{InstructionType::I_TYPE, 0x07});
    instruction_table.emplace("addi", InstructionInfo{InstructionType::I_TYPE, 0x08});
    instruction_table.emplace("addiu", InstructionInfo{InstructionType::I_TYPE, 0x09});
    instruction_table.emplace("slti", InstructionInfo{InstructionType::I_TYPE, 0x0A});
    instruction_table.emplace("sltiu", InstructionInfo{InstructionType::I_TYPE, 0x0B});
    instruction_table.emplace("andi", InstructionInfo{InstructionType::I_TYPE, 0x0C});
    instruction_table.emplace("ori", InstructionInfo{InstructionType::I_TYPE, 0x0D});
    instruction_table.emplace("xori", InstructionInfo{InstructionType::I_TYPE, 0x0E});
    instruction_table.emplace("llo", InstructionInfo{InstructionType::I_TYPE, 0x18});
    instruction_table.emplace("lhi", InstructionInfo{InstructionType::I_TYPE, 0x19});
    instruction_table.emplace("lb", InstructionInfo{InstructionType::I_TYPE, 0x20});
    instruction_table.emplace("lh", InstructionInfo{InstructionType::I_TYPE, 0x21});
    instruction_table.emplace("lw", InstructionInfo{InstructionType::I_TYPE, 0x23});
    instruction_table.emplace("lbu", InstructionInfo{InstructionType::I_TYPE, 0x24});
    instruction_table.emplace("lhu", InstructionInfo{InstructionType::I_TYPE, 0x25});
    instruction_table.emplace("sb", InstructionInfo{InstructionType::I_TYPE, 0x28});
    instruction_table.emplace("sh", InstructionInfo{InstructionType::I_TYPE, 0x29});
    instruction_table.emplace("sw", InstructionInfo{InstructionType::I_TYPE, 0x2B});

    instruction_table.emplace("j", InstructionInfo{InstructionType::J_TYPE, 0x02});
    instruction_table.emplace("jal", InstructionInfo{InstructionType::J_TYPE, 0x03});

    instruction_table.emplace("trap", InstructionInfo{InstructionType::TRAP_TYPE, 0x1A});

    instruction_table.emplace("la", InstructionInfo{InstructionType::I_TYPE, 0x0F});

    // populating the syscall map
    syscall_map["print_int"] = 0;
    syscall_map["print_character"] = 1;
    syscall_map["print_string"] = 2;
    syscall_map["read_int"] = 3;
    syscall_map["read_character"] = 4;
    syscall_map["exit"] = 5;
    
}

std::string trim(const std::string& str) {
    const std::string tab_or_space = " \t";
    const auto string_start = str.find_first_not_of(tab_or_space);
    
    if (string_start == std::string::npos) {
        return "";
    }

    const auto string_end = str.find_last_not_of(tab_or_space);
    const auto string_range = string_end - string_start + 1;
    
    return str.substr(string_start, string_range);
}

void Assembler::pass1(std::istream& input) {
    bool in_data = false;
    uint32_t current_address = 0;
    std::string line;

    while (std::getline(input, line)) {
        line = trim(line);

        if (line.empty()) {
            continue;
        }

        if (line == ".data") {
            in_data = true;
            
            // aligning address to next 4 multiple
            if ((current_address % 4) != 0) {
                current_address = (((current_address / 4) + 1) * 4);
            }
            continue;
        } else if (line == ".text") {
            in_data = false;

            // aligning address to next 4 multiple
            if ((current_address % 4) != 0) {
                current_address = (((current_address / 4) + 1) * 4);
            }

            continue;
        }
        // we check for a label
        auto colon_position = line.find(':');
        
        if (colon_position != std::string::npos) {
            // we save the label
            std::string label = trim(line.substr(0, colon_position));

            
            if (symbol_table.count(label)) {
                // it's an error if we duplicate labels
                std::cerr << "Error: duplicate label '" << label << "'" << std::endl; 
            } else {
                // if not found in the symbol table then we record label and address
                symbol_table[label] = current_address;
                // std::cout << "Found label '" << label << "' at address 0x" << std::hex << current_address << std::dec << std::endl;
            }

            // we remove the label from the line
            line = trim(line.substr(colon_position + 1));
        }

        if (!line.empty()) {
            std::stringstream ss(line);
            std::string first_token;
            ss >> first_token;

            if (in_data) {
                // we handle data directives
                if (first_token == ".word") {
                    std::string value;
                    while (ss >> value) {
                        current_address += 4;
                    }
                } else if (first_token == ".byte") {
                    std::string value;
                    while (ss >> value) {
                        current_address += 1;
                    }
                } else if (first_token == ".space") {
                    uint32_t space_size = 0;
                    ss >> space_size;
                    current_address += space_size;
                } else if (first_token == ".asciiz") {
                    auto first_quote = line.find('"');
                    auto last_quote = line.find_last_of('"');

                    if ((first_quote != std::string::npos) && (last_quote != std::string::npos) && (first_quote < last_quote)) {
                        std::string string_content = line.substr(first_quote + 1, last_quote - first_quote - 1);
                        uint32_t string_length = string_content.length();
                        current_address += string_length + 1;
                    } else {
                        std::cerr << "Malformed string in line " << line << std::endl; 
                    }
                }
            } else {
                current_address += 4;
            }
        }
    }
}

uint8_t Assembler::parse_register(std::string token) {
    token.erase(std::remove(token.begin(), token.end(), ','), token.end());
    token = trim(token);
    if (!register_map.count(token)) {
        throw std::runtime_error(token + ": invalid register name");
    } else {
        return register_map.at(token);
    }
}

void Assembler::parse_mem_operand(std::string token, int16_t& immediate, uint8_t& reg) {
    token = trim(token);
    auto par_begin = token.find('(');
    auto par_end = token.find(')');

    if ((par_begin == std::string::npos) || (par_end == std::string::npos)) {
        throw std::runtime_error("Invalid memory operand format");
    } else {
        immediate = std::stoi(token.substr(0, par_begin));
        std::string register_name = token.substr(par_begin + 1, par_end - par_begin - 1);
        reg = parse_register(register_name);
    }
}

uint32_t Assembler::encode_r_type(const InstructionInfo& info, const std::vector<std::string>& operands) {
    uint8_t opcode = info.opcode;
    uint8_t funct = info.funct;
    uint8_t rd = 0;
    uint8_t rs = 0;
    uint8_t rt = 0;
    uint8_t shamt = 0;

    switch (info.funct) {
        // sll, slr, sra
        case (0x00):
        case (0x02):
        case (0x03): {
            if (operands.size() != 3) {
                throw std::runtime_error("Shift instruction expects 3 operands");
            } else {
                rd = parse_register(operands[0]);
                rt = parse_register(operands[1]);
                shamt = std::stoi(operands[2]);
                break;
            }
        }

        // sllv, srlv, srav
        case (0x04):
        case (0x06):
        case (0x07): {
            if (operands.size() != 3) {
                throw std::runtime_error("Variable shift expexts 3 operands");
            } else {
                rd = parse_register(operands[0]);
                rt = parse_register(operands[1]);
                rs = parse_register(operands[2]);
                break;
            }
        }

        // jr
        case (0x08): {
            if (operands.size() != 1) {
                throw std::runtime_error("jr expects 1 operand");
            } else {
                rs = parse_register(operands[0]);
                break;
            }
        }

        // jalr (rd, rs or just rs)
        case (0x09): {
            if (operands.size() != 1) {
                throw std::runtime_error("jalr expects exactly one register operand");
            } else {
                rs = parse_register(operands[0]);
                rd = 31;
                break;
            }
        }

        // mfhi, mflo
        case (0x10):
        case (0x12): {
            if (operands.size() != 1) {
                throw std::runtime_error("mfhi/mtlo expects 1 operand");
            } else {
                rd = parse_register(operands[0]);
                break;
            }
        }

        // mthi, mtlo
        case (0x11):
        case (0x13): {
            if (operands.size() != 1) {
                throw std::runtime_error("mthi, mtlo expects 1 operand");
            } else {
                rs = parse_register(operands[0]);
                break;
            }
        }

        // mult, multu, div, divu
        case (0x18):
        case (0x19):
        case (0x1A):
        case (0x1B): {
            if (operands.size() != 2) {
                throw std::runtime_error("mult and div instructions expect 2 operands");
            } else {
                rs = parse_register(operands[0]);
                rt = parse_register(operands[1]);
                break;
            }
        }

        // add, addu, sub, subu, and
        // or, xor, nor, slt, sltu
        case (0x20):
        case (0x21):
        case (0x22):
        case (0x23):
        case (0x24):
        case (0x25):
        case (0x26):
        case (0x27):
        case (0x2A):
        case (0x2B): {
            if (operands.size() != 3) {
                throw std::runtime_error("Arithmetic/Logic instrucitons expect 3 operands");
            } else {
                rd = parse_register(operands[0]);
                rs = parse_register(operands[1]);
                rt = parse_register(operands[2]);
                break;
            }
        }

        default: {
            throw std::runtime_error("Unsupported function code for R-type instruction");
        }
    }

    return ((opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | (funct));
}

uint32_t Assembler::encode_i_type(const InstructionInfo& info, const std::vector<std::string>& operands, uint32_t current_address) {
    uint8_t opcode = info.opcode;
    uint8_t rt = 0;
    uint8_t rs = 0;
    int16_t immediate = 0;

    auto calc_branch_off = [&](const std::string& label) {
        if (!symbol_table.count(label)) {
            throw std::runtime_error(label + " not found");
        } else {
            uint32_t target_address = symbol_table.at(label);
            int32_t offset = target_address - (current_address + 4);
            return static_cast<int16_t>(offset / 4);
        }
    };

    switch (info.opcode) {
        // beq, bne
        case (0x04):
        case (0x05): {
            if (operands.size() != 3) {
                throw std::runtime_error("Branch instructions expects 3 operands");
            } else {
                rs = parse_register(operands[0]);
                rt = parse_register(operands[1]);
                immediate = calc_branch_off(trim(operands[2]));
                break;
            }
        }

        // blez, bgtz
        case (0x06):
        case (0x07): {
            if (operands.size() != 2) {
                throw std::runtime_error("Branch on zero instructions expect 2 operands");
            } else {
                rs = parse_register(operands[0]);
                rt = 0;
                immediate = calc_branch_off(trim(operands[1]));
                break;
            }
        }

        // addi, addiu, slti, sltiu
        // andi, ori, xori
        case (0x08):
        case (0x09):
        case (0x0A):
        case (0x0B):
        case (0x0C):
        case (0x0D):
        case (0x0E): {
            if (operands.size() != 3) {
                throw std::runtime_error("Arithmetic logic immediate instructions expect 3 opernds");
            } else {
                rt = parse_register(operands[0]);
                rs = parse_register(operands[1]);
                immediate = std::stoi(operands[2]);
                break;
            }
        }

        // llo, lhi
        case (0x18):
        case (0x19): {
            if (operands.size() != 2) {
                throw std::runtime_error("llo and lhi expect 2 operands");
            } else {
                rt = parse_register(operands[0]);
                immediate = std::stoi(operands[1]);
                rs = 0;
                break;
            }
        }

        // lb, lh, lw, lbu, 
        // lhu, sb, sh, sw
        case (0x20):
        case (0x21):
        case (0x23):
        case (0x24):
        case (0x25):
        case (0x28):
        case (0x29):
        case (0x2B): {
            if (operands.size() != 2) {
                throw std::runtime_error("Load store instructions expect 2 operands");
            } else {
                rt = parse_register(operands[0]);
                parse_mem_operand(operands[1], immediate, rs);
                break;
            }
        }

        // la
        case (0x0F): {
            if (operands.size() != 2) {
                throw std::runtime_error("la instruction expects 2 operands");
            } else {
                rt = parse_register(operands[0]);
                std::string label = trim(operands[1]);
                if (!symbol_table.count(label)) {
                    throw std::runtime_error("unknown label for la instruction: " + label);
                } else {
                    uint32_t address = symbol_table.at(label);
                    if (address > 0xFFFFu) {
                        throw std::runtime_error("label address exceeds 16 bits range");
                    } else {
                        immediate = static_cast<int16_t>(static_cast<uint16_t>(address));
                        break;
                    }
                }
            }
        }

        default: {
            throw std::runtime_error("Unkown opcode for I-type");
        }
    }

    return ((opcode << 26) | (rs << 21) | (rt << 16) | static_cast<uint16_t>(immediate));
}

uint32_t Assembler::encode_j_type(const InstructionInfo& info, const std::vector<std::string>& operands) {
    if (operands.size() != 1) {
        throw std::runtime_error("Jump instruction expects 1 operand");
    } else {
        uint8_t opcode = info.opcode;
        std::string label = trim(operands[0]);

        if (!symbol_table.count(label)) {
            throw std::runtime_error(label + " not found");
        } else {
            uint32_t target_address = symbol_table.at(label);
            uint32_t index = ((target_address >> 2) & (0x03FFFFFFu));
            return (((static_cast<uint32_t>(opcode)) << 26) | index);
        }
    }
}

uint32_t Assembler::encode_trap_type(const InstructionInfo& info, const std::vector<std::string>& operands) {
    uint8_t opcode = info.opcode;

    if (operands.size() != 1) {
        throw std::runtime_error("Syscall requires exactly one immediate operand");
    } else {
        std::string syscall_name = trim(operands[0]);

        if (!syscall_map.count(syscall_name)) {
            throw std::runtime_error("Unknown syscall name");
        } else {
            uint16_t code = syscall_map.at(syscall_name);
            return ((opcode << 26) | (code & 0xFFFF));
        }
    }
}

void Assembler::pass2(std::istream& input) {
    bool in_data = false;
    uint32_t current_address = 0;
    std::string line;
    int line_num = 0;

    binary_output.clear();

    while (std::getline(input, line)) {
        line_num++;
        line = trim(line);

        if (line.empty()) {
            continue;
        }

        if (line == ".data") {
            in_data = true;

            if ((current_address % 4) != 0) {
                current_address = ((current_address / 4) + 1) * 4;
            }

            continue;
        } else if (line == ".text") {
            in_data = false;

            if ((current_address % 4) != 0) {
                current_address = ((current_address / 4) + 1) * 4;
            }

            continue;
        }

        auto colon_position = line.find(':');

        if (colon_position != std::string::npos) {
            line = trim(line.substr(colon_position + 1));
        }

        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string operation;
        ss >> operation;

        if (in_data) {
            if (operation == ".word") {
                uint32_t value;
                
                while (ss >> value) {
                    binary_output.push_back((value >> 0) & 0xFF);
                    binary_output.push_back((value >> 8) & 0xFF);
                    binary_output.push_back((value >> 16) & 0xFF);
                    binary_output.push_back((value >> 24) & 0xFF);
                    current_address += 4;
                }
            } else if (operation == ".byte") {
                int value;

                while (ss >> value) {
                    binary_output.push_back(static_cast<uint8_t>(value));
                    current_address += 1;
                }
            } else if (operation == ".space") {
                uint32_t size;
                ss >> size;

                for (uint32_t i = 0; i < size; ++i) {
                    binary_output.push_back(0);
                }

                current_address += size;
            } else if (operation == ".asciiz") {
                auto first_quote = line.find('"');
                auto last_quote = line.find_last_of('"');

                if ((first_quote != std::string::npos) && (last_quote != std::string::npos) && (first_quote < last_quote)) {
                    std::string string_content = line.substr(first_quote + 1, last_quote - first_quote - 1);
                    for (char c : string_content) {
                        binary_output.push_back(static_cast<uint8_t>(c));
                    }

                    binary_output.push_back(0);
                    current_address += string_content.length() + 1;
                } else {
                    std::cerr << "Error: malformed string in line " << line_num << std::endl; 
                }
            }
        } else {
            if (!(instruction_table.count(operation))) {
                std::cerr << "Error on line " << line << std::endl;
                continue;
            } else {
                std::vector<std::string> operands;
                std::string operand;

                while (std::getline(ss, operand, ',')) {
                    operands.push_back(trim(operand));
                }

                uint32_t machine_code = 0;
                const auto& info = instruction_table.at(operation);

                try {
                    switch (info.type) {
                        case (InstructionType::R_TYPE): {
                            machine_code = encode_r_type(info, operands);
                            break;
                        }

                        case (InstructionType::I_TYPE): {
                            machine_code = encode_i_type(info, operands, current_address);
                            break;
                        }

                        case (InstructionType::J_TYPE): {
                            machine_code = encode_j_type(info, operands);
                            break;
                        }

                        case (InstructionType::TRAP_TYPE): {
                            machine_code = encode_trap_type(info, operands);
                            break;
                        }
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error assembling in line " << line << " " << e.what() << std::endl;
                    continue;
                }

                binary_output.push_back((machine_code >> 0) & 0xFF);
                binary_output.push_back((machine_code >> 8) & 0xFF);
                binary_output.push_back((machine_code >> 16) & 0xFF);
                binary_output.push_back((machine_code >> 24) & 0xFF);
                current_address += 4;
            }
        }
    }
}

std::vector<uint8_t> Assembler::run_assembly(std::istream& input) {
    binary_output.clear();

    std::stringstream buffer;
    buffer << input.rdbuf();

    pass1(buffer);

    buffer.clear();
    buffer.seekg(0, std::ios::beg);

    pass2(buffer);

    return binary_output;
}

void Assembler::process(std::istream& input, std::ostream& output, bool hex_output) {
    const auto machine_code = run_assembly(input);

    if (hex_output) {
        output << std::hex << std::setfill('0');

        for (size_t i = 0; i < machine_code.size(); i += 4) {
            if ((i + 3) < machine_code.size()) {
                uint32_t word = (static_cast<uint32_t>(machine_code[i+3]) << 24) |
                                (static_cast<uint32_t>(machine_code[i+2]) << 16) |
                                (static_cast<uint32_t>(machine_code[i+1]) << 8) |
                                (static_cast<uint32_t>(machine_code[i]));
                output << "0x" << std::setw(8) << word << std::endl;
            }
        }

    } else {
        
        if (output.good()) {
            output.write(reinterpret_cast<const char*>(machine_code.data()), machine_code.size());
        } else {
            std::cout << "Error: can't write to output stream" << std::endl;
        }
    }
}

const std::unordered_map<std::string, uint32_t>& Assembler::get_symbol_table() const {
    return symbol_table;
}