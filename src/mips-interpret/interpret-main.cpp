#include "../mips-core/machine_state.hpp"
#include "../mips-core/interpreter.hpp"
#include "../mips-core/assembler.hpp"

#include <vector>
#include <iostream>
#include <stdexcept>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Correct format is mips-interpret <filename.bin>" << std::endl;
        return 1;
    } else {
        std::ifstream input_file(argv[1]);
        
        if (!input_file.is_open()) {
            std::cerr << "Error: could not open file " << argv[1] << std::endl;
            return 1;
        } else {
            Assembler assembler;
            std::stringstream binary_stream;

            try {
                assembler.process(input_file, binary_stream, false);
            } catch (const std::exception& e) {
                std::cerr << "Assembly error: " << e.what() << std::endl;
                return 1;
            }

            std::string binary_string = binary_stream.str();
            std::vector<uint8_t> machine_code(binary_string.begin(), binary_string.end());

            const auto& symbol_table = assembler.get_symbol_table();

            if (!symbol_table.count("main")) {
                std::cerr << "Error: main label not found in assembly file" << std::endl;
                return 1;
            } else {
                uint32_t main_address = symbol_table.at("main");

                MachineState state(1024 * 1024 * 4);

                if (machine_code.size() > 4u * 1024u * 1024u) {
                    std::cerr << "Error: exceeded available memory" << std::endl;
                    return 1;
                }

                for (size_t i = 0; i < machine_code.size(); ++i) {
                    state.write_byte(i, machine_code[i]);
                }

                state.set_pc(main_address);

                Interpreter interpreter(state);

                try {
                    interpreter.run();
                } catch (const std::exception& e) {
                    std::cerr << "Runtime error: " << e.what() << std::endl;
                    return 1;
                }

                std::cout << "End of execution" << std::endl;

                return 0;
            }
        }
    }
}
