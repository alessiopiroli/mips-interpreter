#include "gtest/gtest.h"
#include "assembler.hpp"

class MoveToTest : public ::testing::Test {
protected:
    Assembler assembler;
};

TEST_F(MoveToTest, MthiTest) {
    std::string assembly_code = "mthi $t0";
    std::stringstream code_stream(assembly_code);
    std::stringstream binary_output;

    // opcode = 000000
    // rs = 01000
    // rt = 00000
    // rd = 00000
    // shamt = 00000 
    // funct = 010001
    // Instruction
    // 000000'01000'00000'00000'00000'010001
    // 0000'0001'0000'0000'0000'0000'0001'0001
    // 0x01'00'00'11

    std::vector<uint8_t> expected_machine_code = {
        0x11, 0x00, 0x00, 0x01
    };

    std::string expected_output_str(expected_machine_code.begin(), expected_machine_code.end());

    assembler.process(code_stream, binary_output, false);

    ASSERT_EQ(binary_output.str(), expected_output_str);
}