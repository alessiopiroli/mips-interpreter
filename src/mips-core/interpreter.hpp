#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>

#include "machine_state.hpp"
#include "instruction.hpp"

using Executor = std::function<void(const Instruction&)>;

class Interpreter {
private:
    MachineState& machine_state;
    bool running;

    std::unordered_map<uint8_t, Executor> r_type_funct_map;
    std::unordered_map<uint8_t, Executor> opcode_map;

public:
    explicit Interpreter(MachineState& machine_state_);
    void execute_instruction(const Instruction& instruction);
    void run();

    void step();
    bool is_running() const;
    void start();
};