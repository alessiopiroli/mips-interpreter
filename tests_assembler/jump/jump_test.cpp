#include "gtest/gtest.h"
#include "assembler.hpp"

class JumpTest : public ::testing::Test {
protected:
    Assembler assembler;
};

TEST_F(JumpTest, JalTest) {
    std::string assembly_code =
    ".text\n"
    "\t jal target \n"
    "add $zero, $zero, $zero\n"
    "target:\n"
    "\t add $zero, $zero, $zero";


    std::stringstream code_stream(assembly_code);
    std::stringstream binary_output;

    // jal target
    // opcode = 000011
    // immediate = 00000000000000000000000010
    // Instruction
    // 000011'00000000000000000000000010
    // 0000'1100'0000'0000'0000'0000'0000'0010
    // 0x0C'00'00'02

    // add $zero, $zero, $zero
    // opcode = 000000
    // rs = 00000
    // rt = 00000
    // rd = 00000
    // shamt = 00000
    // funct = 100000
    // Instruction
    // 000000'00000'00000'00000'00000'100000
    // 0000'0000'0000'0000'0000'0000'0010'0000
    // 0x00'00'00'20

    std::vector<uint8_t> expected_machine_code = {
        0x02, 0x00, 0x00, 0x0C,
        0x20, 0x00, 0x00, 0x00,
        0x20, 0x00, 0x00, 0x00
    };

    std::string expected_output_str(expected_machine_code.begin(), expected_machine_code.end());

    assembler.process(code_stream, binary_output, false);

    ASSERT_EQ(binary_output.str(), expected_output_str);
}