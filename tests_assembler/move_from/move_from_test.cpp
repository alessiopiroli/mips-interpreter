#include "gtest/gtest.h"
#include "assembler.hpp"

class MoveFromTest : public ::testing::Test {
protected:
    Assembler assembler;
};

TEST_F(MoveFromTest, MfhiTest) {
    std::string assembly_code = "mfhi $t0";
    std::stringstream code_stream(assembly_code);
    std::stringstream binary_output;

    // opcode = 000000
    // rs = 00000
    // rt = 00000
    // rd = 01000
    // shamt = 00000 
    // funct = 010000
    // Instruction
    // 000000'00000'00000'01000'00000'010000
    // 0000'0000'0000'0000'0100'0000'0001'0000
    // 0x00'00'40'10

    std::vector<uint8_t> expected_machine_code = {
        0x10, 0x40, 0x00, 0x00
    };

    std::string expected_output_str(expected_machine_code.begin(), expected_machine_code.end());

    assembler.process(code_stream, binary_output, false);

    ASSERT_EQ(binary_output.str(), expected_output_str);
}