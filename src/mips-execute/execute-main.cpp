#include "../mips-core/machine_state.hpp"
#include "../mips-core/interpreter.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::ifstream bin_file(argv[1], std::ios::in | std::ios::binary);

    if (!bin_file) {
        std::cerr << "Error: can't open file" << std::endl;
        return 1;
    }

    bin_file.seekg(0, std::ios::end);
    std::streamsize size = bin_file.tellg();
    bin_file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    if (!bin_file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        std::cerr << "Error: Could not read from file " << argv[1] << std::endl;
        return 1;
    }

    MachineState state(1024 * 1024 * 4);

    for(size_t i = 0; i < buffer.size(); ++i) {
        state.write_byte(i, buffer[i]);
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

