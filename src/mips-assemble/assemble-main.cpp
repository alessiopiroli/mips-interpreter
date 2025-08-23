#include "assembler.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    
    Assembler assembler;

    if (argc == 1) {
        std::cout << "Assembling from the standard input (std::cin). ";
        std::cout << "Press Ctrl+D when done" << std::endl;
        assembler.process(std::cin, std::cout, true);
    } else if (argc == 2) {
        std::cout << "You have selected the option with an assembly input file" << std::endl;
        std::string input_filename = argv[1];
        std::ifstream input_file(input_filename);

        if (!input_file.is_open()) {
            std::cerr << "ERROR: could not open input file" << std::endl;
            return 1;
        } else {
            assembler.process(input_file, std::cout, true);
        }

    } else if (argc == 3) {
        std::cout << "You have selected the option with an input.asm and output.bin" << std::endl;

        std::string input_filename = argv[1];
        std::string output_filename = argv[2];
        
        std::ifstream input_file(input_filename);
        std::ofstream output_file(output_filename);

        if (!input_file.is_open()) {
            std::cerr << "Could not open input file" << std::endl;
            return 1;
        } else if (!output_file.is_open()) {
            std::cerr << "Could not open output file" << std::endl;
        } else {
            assembler.process(input_file, output_file, false);
        }

    } else {
        std::cout << "Invalid program functionality selection" << std::endl;
    }
}