#include "../mips-core/machine_state.hpp"
#include "../mips-core/interpreter.hpp"

#include <vector>
#include <iostream>  // Required for std::cout and std::cerr
#include <stdexcept> // Required for std::exception

int main(int argc, char* argv[]) {

    const std::vector<uint32_t> program = {
        0x2404002A, // addiu $a0,$zero,42
        0x68000000, // trap 0  (print_int)
        0x2404000A, // addiu $a0,$zero,10 ('\n')
        0x68000001, // trap 1  (print_character)
        0x68000005  // trap 5  (exit)
    };

    MachineState state(1024 * 1024); // 1MB of memory

    for (size_t i = 0; i < program.size(); ++i) {
        state.write_word(i * 4, program[i]);
    }

    Interpreter interpreter(state);

    try {
        interpreter.run();
    } catch (const std::exception& e) {
        std::cerr << "RUNTIME ERROR: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\nExecution finished successfully." << std::endl;
    return 0;
}
