#include "interpreter.hpp"
#include "instruction.hpp"

#include <iostream>

Interpreter::Interpreter(MachineState& machine_state_) : 
    machine_state{machine_state_}, running{false} {
    // SHIFT

    // sll rd, rt, shamt
    r_type_funct_map[0x00] = [this](const Instruction& inst) {
        int32_t val_to_shift = machine_state.get_register(inst.rt());
        int32_t shifted_value = val_to_shift << inst.shamt();
        machine_state.set_register(inst.rd(), static_cast<uint32_t>(shifted_value));
    };

    // srl rd, rt, shhamt
    r_type_funct_map[0x02] = [this](const Instruction& inst) {
        uint32_t value_to_shift = machine_state.get_register(inst.rt());
        uint32_t result = value_to_shift >> inst.shamt();
        machine_state.set_register(inst.rd(), result);
    };

    // sra rd, rt, shamt
    r_type_funct_map[0x03] = [this](const Instruction& inst) {
        int32_t value_to_shift = machine_state.get_register(inst.rt());
        int32_t result = value_to_shift >> inst.shamt();
        machine_state.set_register(inst.rd(), static_cast<uint32_t>(result));
    };

    // sllv rd, rt, rs
    r_type_funct_map[0x04] = [this](const Instruction& inst) {
        int32_t value_to_shift = (machine_state.get_register(inst.rt()));
        uint32_t shift_amount = machine_state.get_register(inst.rs()) & 0x1F;
        int32_t result = value_to_shift << shift_amount;
        machine_state.set_register(inst.rd(), static_cast<uint32_t>(result));
    };

    // srlv rd, rt, rs
    r_type_funct_map[0x06] = [this](const Instruction& inst) {
        uint32_t value_to_shift = machine_state.get_register(inst.rt());
        uint32_t shift_amount = machine_state.get_register(inst.rs()) & 0x1F;
        uint32_t result = value_to_shift >> shift_amount;
        machine_state.set_register(inst.rd(), result);
    };

    // srav rd, rt, rs
    r_type_funct_map[0x07] = [this](const Instruction& inst) {
        int32_t value_to_shift = static_cast<int32_t>(machine_state.get_register(inst.rt()));
        uint32_t shift_amount = machine_state.get_register(inst.rs()) & 0x1F;
        int32_t result = value_to_shift >> shift_amount;
        machine_state.set_register(inst.rd(), static_cast<uint32_t>(result));
    };

    // JUMP REG

    // jr rs
    r_type_funct_map[0x08] = [this](const Instruction& inst) {
        uint32_t target_address = machine_state.get_register(inst.rs());
        if ((target_address % 4) != 0) {
            throw std::runtime_error("Error: jr jump to unaligned address");
        } else {
            machine_state.set_pc(target_address);
        }
    };

    // jalr
    r_type_funct_map[0x09] = [this](const Instruction& inst) {
        uint32_t target_address = machine_state.get_register(inst.rs());
        if ((target_address % 4) != 0) {
            throw std::runtime_error("Error: jalr jump to unaligned address");
        } else {
            machine_state.set_register(31, machine_state.get_pc());
            machine_state.set_pc(target_address);
        }
    };

    // MOVE FROM

    // mfhi rd
    r_type_funct_map[0x10] = [this](const Instruction& inst) {
        machine_state.set_register(inst.rd(), machine_state.get_hi());
    };

    // mthi rs
    r_type_funct_map[0x11] = [this](const Instruction& inst) {
        machine_state.set_hi(machine_state.get_register(inst.rs()));
    };

    // MOVE TO

    // mflo rd
    r_type_funct_map[0x12] = [this](const Instruction& inst) {
        machine_state.set_register(inst.rd(), machine_state.get_lo());
    };

    // mtlo rs
    r_type_funct_map[0x13] = [this](const Instruction& inst) {
        machine_state.set_lo(machine_state.get_register(inst.rs()));
    };

    // DIV_MULT

    // mult
    r_type_funct_map[0x18] = [this](const Instruction& inst) {
        int64_t first_value = static_cast<int64_t>(static_cast<int32_t>(machine_state.get_register(inst.rs())));
        int64_t second_value = static_cast<int64_t>(static_cast<int32_t>(machine_state.get_register(inst.rt())));
        int64_t signed_result = first_value * second_value;

        uint64_t unsigned_result = static_cast<uint64_t>(signed_result);
        machine_state.set_lo(static_cast<uint32_t>(unsigned_result & 0xFFFFFFFFu));
        machine_state.set_hi(static_cast<uint32_t>(unsigned_result >> 32));
    };

    // multu rs, rt
    r_type_funct_map[0x19] = [this](const Instruction& inst) {    
    uint64_t first_value  = static_cast<uint64_t>(machine_state.get_register(inst.rs()));
    uint64_t second_value = static_cast<uint64_t>(machine_state.get_register(inst.rt()));
    uint64_t result = first_value * second_value;
    machine_state.set_lo(static_cast<uint32_t>(result));
    machine_state.set_hi(static_cast<uint32_t>(result >> 32));
    };

    // div rs, rt
    r_type_funct_map[0x1A] = [this](const Instruction& inst) {
        int32_t numerator = static_cast<int32_t>(machine_state.get_register(inst.rs()));
        int32_t denominator = static_cast<int32_t>(machine_state.get_register(inst.rt()));
        
        if (denominator != 0) {
            machine_state.set_lo(static_cast<uint32_t>(numerator / denominator));
            machine_state.set_hi(static_cast<uint32_t>(numerator % denominator));
        } else {
            throw std::runtime_error("Error: division by zero");
        }
    };

    // divu rs, rt // TO FIX
    r_type_funct_map[0x1B] = [this](const Instruction& inst) {
        uint32_t numerator = machine_state.get_register(inst.rs());
        uint32_t denominator = machine_state.get_register(inst.rt());

        if (denominator != 0) {
            machine_state.set_lo(numerator / denominator);
            machine_state.set_hi(numerator % denominator);
        } else {
            throw std::runtime_error("Error: division by zero");
        }
    };

    // ARITH LOGIC

    // add rf, rs, rt
    r_type_funct_map[0x20] = [this](const Instruction& inst) {
        int32_t val1 = static_cast<int32_t>(machine_state.get_register(inst.rs()));
        int32_t val2 = static_cast<int32_t>(machine_state.get_register(inst.rt()));
        int32_t result = val1 + val2;
        machine_state.set_register(inst.rd(), static_cast<uint32_t>(result));
    };

    // addu rd, rs, rt
    r_type_funct_map[0x21] = [this](const Instruction& inst) {
        uint32_t val1 = machine_state.get_register(inst.rs());
        uint32_t val2 = machine_state.get_register(inst.rt());
        uint32_t result = val1 + val2;
        machine_state.set_register(inst.rd(), result);
    };

    // sub rd, rs, rt
    r_type_funct_map[0x22] = [this](const Instruction& inst) {
        int32_t val1 = static_cast<int32_t>(machine_state.get_register(inst.rs()));
        int32_t val2 = static_cast<int32_t>(machine_state.get_register(inst.rt()));
        int32_t result = val1 - val2;
        machine_state.set_register(inst.rd(), static_cast<uint32_t>(result));
    };

    // subu rd, rs, rt
    r_type_funct_map[0x23] = [this](const Instruction& inst) {
        uint32_t val1 = machine_state.get_register(inst.rs());
        uint32_t val2 = machine_state.get_register(inst.rt());
        uint32_t result = val1 - val2;
        machine_state.set_register(inst.rd(), result);
    };

    // and rd, rs, rt
    r_type_funct_map[0x24] = [this](const Instruction& inst) {
        uint32_t val1 = machine_state.get_register(inst.rs());
        uint32_t val2 = machine_state.get_register(inst.rt());
        uint32_t result = val1 & val2;
        machine_state.set_register(inst.rd(), result);
    };

    // or, rd, rs, rt
    r_type_funct_map[0x25] = [this](const Instruction& inst) {
        uint32_t val1 = machine_state.get_register(inst.rs());
        uint32_t val2 = machine_state.get_register(inst.rt());
        uint32_t result = val1 | val2;
        machine_state.set_register(inst.rd(), result);
    };

    // xor rd, rs, rt
    r_type_funct_map[0x26] = [this](const Instruction& inst) {
        uint32_t val1 = machine_state.get_register(inst.rs());
        uint32_t val2 = machine_state.get_register(inst.rt());
        uint32_t result = val1 ^ val2;
        machine_state.set_register(inst.rd(), result);
    };

    // nor rd, rs, rt
    r_type_funct_map[0x27] = [this](const Instruction& inst) {
        uint32_t val1 = machine_state.get_register(inst.rs());
        uint32_t val2 = machine_state.get_register(inst.rt());
        uint32_t result = ~(val1 | val2);
        machine_state.set_register(inst.rd(), result);
    };

    // slt rd, rs, rt
    r_type_funct_map[0x2A] = [this](const Instruction& inst) {
        auto val1 = static_cast<int32_t>(machine_state.get_register(inst.rs()));
        auto val2 = static_cast<int32_t>(machine_state.get_register(inst.rt()));
        machine_state.set_register(inst.rd(), (val1 < val2) ? 1 : 0);
    };

    // sltu rd, rs, rt
    r_type_funct_map[0x2B] = [this](const Instruction& inst) {
        uint32_t val1 = machine_state.get_register(inst.rs());
        uint32_t val2 = machine_state.get_register(inst.rt());
        machine_state.set_register(inst.rd(), (val1 < val2) ? 1 : 0);
    };

    // BRANCH

    // beq rs, rt, label
    opcode_map[0x04] = [this](const Instruction& inst) {
        if (machine_state.get_register(inst.rs()) == machine_state.get_register(inst.rt())) {
            uint32_t tmp = (static_cast<uint32_t>(static_cast<uint16_t>(inst.immediate())) << 2) & 0xFFFFu;
            int32_t offset = static_cast<int16_t>(tmp);
            machine_state.set_pc(machine_state.get_pc() + offset);
        }
    };

    // bne rs, rt, label
    opcode_map[0x05] = [this](const Instruction& inst) {
        if (machine_state.get_register(inst.rs()) != machine_state.get_register(inst.rt())) {
            uint32_t tmp = (static_cast<uint32_t>(static_cast<uint16_t>(inst.immediate())) << 2) & 0xFFFFu;
            int32_t offset = static_cast<int16_t>(tmp);
            machine_state.set_pc(machine_state.get_pc() + offset);
        }
    };

    // BRANCH ZERO

    // blez rs, label
    opcode_map[0x06] = [this](const Instruction& inst) {
        if (static_cast<int32_t>(machine_state.get_register(inst.rs())) <= 0) {
            uint32_t tmp = (static_cast<uint32_t>(static_cast<uint16_t>(inst.immediate())) << 2) & 0xFFFFu;
            int32_t offset = static_cast<int16_t>(tmp);
            machine_state.set_pc(machine_state.get_pc() + offset);
        }
    };

    // bgtz rs, label
    opcode_map[0x07] = [this](const Instruction& inst) {
        if (static_cast<int32_t>(machine_state.get_register(inst.rs())) > 0) {
            uint32_t tmp = (static_cast<uint32_t>(static_cast<uint16_t>(inst.immediate())) << 2) & 0xFFFFu;
            int32_t offset = static_cast<int16_t>(tmp);
            machine_state.set_pc(machine_state.get_pc() + offset);
        }
    };


    // ARTIH_LOGIC_IMM

    // addi rt, rs, immediate
    opcode_map[0x08] = [this](const Instruction& inst) {
        uint8_t rs = inst.rs();
        uint8_t rt = inst.rt();
        int16_t immediate = inst.immediate();
        uint32_t val1 = machine_state.get_register(rs);
        uint32_t result = val1 + immediate;
        machine_state.set_register(rt, result);
    };

    // addiu rt, rs, immediate
    opcode_map[0x09] = [this](const Instruction& inst) {
        uint8_t rs = inst.rs();
        uint8_t rt = inst.rt();
        int16_t immediate = inst.immediate();
        uint32_t val1 = machine_state.get_register(rs);
        uint32_t result = val1 + immediate;
        machine_state.set_register(rt, result);
    };

    // slti rt, rs, immediate
    opcode_map[0x0A] = [this](const Instruction& inst) {
        uint8_t rs = inst.rs();
        uint8_t rt = inst.rt();
        int16_t immediate = inst.immediate();
        int32_t val1 = static_cast<int32_t>(machine_state.get_register(rs));
        uint32_t result = (val1 < immediate) ? 1 : 0;
        machine_state.set_register(rt, result);
    };

    // sltiu rt, rs, immediate
    opcode_map[0x0B] = [this](const Instruction& inst) {
        uint8_t rs = inst.rs();
        uint8_t rt = inst.rt();
        uint32_t val = machine_state.get_register(rs);
        uint32_t immediate = static_cast<uint32_t>(static_cast<int32_t>(static_cast<int16_t>(inst.immediate())));
        machine_state.set_register(rt, (val < immediate) ? 1u : 0u);
    };

    // andi rt, rs, immediate
    opcode_map[0x0C] = [this](const Instruction& inst) {
        uint8_t rs = inst.rs();
        uint8_t rt = inst.rt();
        uint16_t immediate = inst.immediate();
        uint32_t val = machine_state.get_register(rs);
        uint32_t result = (val & immediate);
        machine_state.set_register(rt, result);
    };

    // ori rt, rs, immediate
    opcode_map[0x0D] = [this](const Instruction& inst) {
        uint8_t rs = inst.rs();
        uint8_t rt = inst.rt();
        uint16_t immediate = inst.immediate();
        uint32_t val = machine_state.get_register(rs);
        uint32_t result = (val | immediate);
        machine_state.set_register(rt, result);
    };

    // xori rt, rs, immediate
    opcode_map[0x0E] = [this](const Instruction& inst) {
        uint8_t rs = inst.rs();
        uint8_t rt = inst.rt();
        uint16_t immediate = inst.immediate();
        uint32_t val = machine_state.get_register(rs);
        uint32_t result = (val ^ immediate);
        machine_state.set_register(rt, result);
    };

    // LOAD IMMEDIATE

    // llo
    opcode_map[0x18] = [this](const Instruction& inst) {
        uint8_t  rt  = inst.rt();
        uint16_t imm = static_cast<uint16_t>(inst.immediate());

        uint32_t original_rt = machine_state.get_register(rt);
        uint32_t new_rt = (original_rt & 0xFFFF0000u) | static_cast<uint32_t>(imm);

        machine_state.set_register(rt, new_rt);
    };

    // lhi
    opcode_map[0x19] = [this](const Instruction& inst) {
        uint8_t  rt  = inst.rt();
        uint16_t imm = static_cast<uint16_t>(inst.immediate());

        uint32_t original_rt = machine_state.get_register(rt);
        uint32_t new_rt = (original_rt & 0x0000FFFFu) | (static_cast<uint32_t>(imm) << 16);

        machine_state.set_register(rt, new_rt);
    };

    // LOAD_STORE

    // lb rt, offset(rs)
    opcode_map[0x20] = [this](const Instruction& inst) {
        uint32_t address = machine_state.get_register(inst.rs()) + static_cast<int16_t>(inst.immediate());
        uint32_t value = machine_state.read_byte_signed(address);
        machine_state.set_register(inst.rt(), value);
    };

    // lh rt, offset(rs)
    opcode_map[0x21] = [this](const Instruction& inst) {
        uint32_t address = machine_state.get_register(inst.rs()) + static_cast<int16_t>(inst.immediate());
        uint32_t value = machine_state.read_half_word_signed(address);
        machine_state.set_register(inst.rt(), value);
    };

    // lw rt, offset(rs)
    opcode_map[0x23] = [this](const Instruction& inst) {
        uint8_t rs = inst.rs();
        uint8_t rt = inst.rt();
        int16_t offset = inst.immediate();
        uint32_t address = machine_state.get_register(rs) + offset;
        uint32_t loaded_value = machine_state.read_word(address);
        machine_state.set_register(rt, loaded_value);
    };

    // lbu rt, offset(rs)
    opcode_map[0x24] = [this](const Instruction& inst) {
        uint32_t address = machine_state.get_register(inst.rs()) + static_cast<int16_t>(inst. immediate());
        uint32_t value = machine_state.read_byte_unsigned(address);
        machine_state.set_register(inst.rt(), value);
    };

    // lhu rt, offset(rs)
    opcode_map[0x25] = [this](const Instruction& inst) {
        uint32_t address = machine_state.get_register(inst.rs()) + static_cast<int16_t>(inst.immediate());
        uint32_t value = machine_state.read_half_word_unsigned(address);
        machine_state.set_register(inst.rt(), value);
    };

    // sb rt, offset(rs)
    opcode_map[0x28] = [this](const Instruction& inst) {
        uint32_t address = machine_state.get_register(inst.rs()) + static_cast<int16_t>(inst.immediate());
        uint8_t value = machine_state.get_register(inst.rt());
        machine_state.write_byte(address, value);
    };

    // sh rt, offset(rs)
    opcode_map[0x29] = [this](const Instruction& inst) {
        int32_t tmp = static_cast<int32_t>(machine_state.get_register(inst.rs())) + static_cast<int16_t>(inst.immediate());
        uint32_t address = static_cast<uint32_t>(tmp);

        if ((address % 2) != 0) {
            throw std::runtime_error("Address alignment error for sh operation");
        } else {
            uint16_t value = static_cast<uint16_t>(machine_state.get_register(inst.rt()));
            machine_state.write_half_word(address, value);
        }
    };

    // sw rt, offset(rs)
    opcode_map[0x2B] = [this](const Instruction& inst) {
        int32_t tmp = static_cast<int32_t>(machine_state.get_register(inst.rs())) + static_cast<int16_t>(inst.immediate());
        uint32_t address = static_cast<uint32_t>(tmp);
        
        if ((address % 4) != 0) {
            throw std::runtime_error("Address alignment error for sw operation");
        } else {
            uint32_t value = machine_state.get_register(inst.rt());
            machine_state.write_word(address, value);
        }
    };

    // JUMP

    // j target
    opcode_map[0x02] = [this](const Instruction& inst) {
        uint32_t target = inst.address() & 0x03FFFFFFu;
        machine_state.set_pc(target);
    };

    // jal target
    opcode_map[0x03] = [this](const Instruction& inst) {
        uint32_t return_address = machine_state.get_pc();
        machine_state.set_register(31, return_address);
        uint32_t target = inst.address() & 0x03FFFFFFu;
        machine_state.set_pc(target);
    };

    // la
    opcode_map[0x0F] = [this](const Instruction& inst) {
        uint32_t immediate = static_cast<uint16_t>(inst.immediate());
        machine_state.set_register(inst.rt(), immediate);
    };

    opcode_map[0x1A] = [this](const Instruction& inst) {
        uint16_t syscall_code = inst.immediate();

        switch (syscall_code) {
            // print integer
            // integer is in a0 (4)
            case 0: {
                std::cout << static_cast<uint32_t>(machine_state.get_register(4)) << "\n";
                break;
            }

            // print character
            // char is in a0 (4)
            case 1: {
                std::cout << static_cast<char>(machine_state.get_register(4) & 0xFF);
                break;
            }

            // print string
            // address string is in a0
            case 2: {
                uint32_t address = machine_state.get_register(4);
                
                while (true) {
                    char c = static_cast<char>(machine_state.read_byte_unsigned(address++));
                    
                    if (c == '\0') {
                        break;
                    }

                    std::cout << c;
                }

                break;
            }

            // read int
            case 3: {
                int32_t input_value;

                if (std::cin >> input_value) {
                    machine_state.set_register(2, static_cast<uint32_t>(input_value));
                } else {
                    std::cerr << "ERROR: read int failed" << std::endl;
                }

                break;
            }

            // read char
            case 4: {
                char input_char;
                if (std::cin >> input_char) {
                    machine_state.set_register(2, static_cast<uint32_t>(input_char));
                } else {
                    std::cerr << "ERROR: read char failed" << std::endl;
                }

                break;
            }

            // exit
            case 5: {
                this->running = false;
                break;
            }

            default: {
                std::cerr << "Unrecognized syscall code: " << syscall_code << std::endl;
                this->running = false;
                break;
            }
        }
    };
}

void Interpreter::execute_instruction(const Instruction& instruction) {
    uint8_t opcode = instruction.opcode();

    if (opcode == 0x00) {
        // register instruction
        uint8_t funct = instruction.funct();

        // checking if function exists
        if (r_type_funct_map.count(funct)) {
            r_type_funct_map.at(funct)(instruction);
        } else {
            std::cerr << "Unimplemented register instruction (funct=0x" << std::hex << int(funct) << ")\n";
            running = false;
        }
    } else {
        if (opcode_map.count(opcode)) {
            opcode_map.at(opcode)(instruction);
        } else {
            std::cerr << "Unimplemented opcode 0x" << std::hex << int(opcode) << "\n" << std::endl;
            running = false;
        }
    }
}

void Interpreter::start() {
    running = true;
}

bool Interpreter::is_running() const {
    return running;
}

void Interpreter::step() {
    if (!running) {
        return;
    } else {
        uint32_t pc = machine_state.get_pc();
        uint32_t word;

        try {
            word = machine_state.read_word(pc);
        } catch (const std::out_of_range&) {
            std::cerr << "PC out of bounds at 0x" << std::hex << pc << std::dec << std::endl;
            return;
        }

        Instruction inst(word);
        machine_state.set_pc(pc + 4);
        execute_instruction(inst);
    }
}

void Interpreter::run() {
    start();
    while (running) {
        step();
    }
}