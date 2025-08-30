#include "gtest/gtest.h"
#include "assembler.hpp"

class BranchZeroTest : public ::testing::Test {
protected:
    Assembler assembler;
};

TEST_F(BranchZeroTest, BlezTest) {
    std::string assembly_code =
        ".text \n"
        "loop: \n" // should be address 0x00
        "blez $zero, loop";

    // beq $zero, $zero, loop
    // opcode = 000110
    // rs = $zero = 00000
    // rt = $zero = 00000
    // offset = - 1 = 0000'0000'0000'0001
    // = 1111'1111'1111'1110 + 1
    // = 1111'1111'1111'1111
    // Instruction
    // 000110'00000'00000'1111'1111'1111'1111
    // 0001'1000'0000'0000'1111'1111'1111'1111
    // 0x18'00'FF'FF


    std::stringstream code_stream(assembly_code);
    std::stringstream binary_output;

    std::vector<uint8_t> expected_machine_code = {
        0xFF, 0xFF, 0x00, 0x18
    };


    std::string expected_output_str(expected_machine_code.begin(), expected_machine_code.end());

    assembler.process(code_stream, binary_output, false);

    ASSERT_EQ(binary_output.str(), expected_output_str);
}