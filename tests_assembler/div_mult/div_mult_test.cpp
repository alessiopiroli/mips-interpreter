#include "gtest/gtest.h"
#include "assembler.hpp"

class DivMultTest : public ::testing::Test {
protected:
    Assembler assembler;
};

TEST_F(DivMultTest, DivTest) {
    std::string assembly_code = "div $t0, $t1";
    std::stringstream code_stream(assembly_code);
    std::stringstream binary_output;

    // opcode = 000000
    // rs = $t0 = reg. 8 = 01000
    // rt = $t1 = reg. 9 = 01001
    // rd = 00000
    // shamt = 00000
    // funct = 011010
    // Instruction
    // 000000'01000'01001'00000'00000'011010
    // 0000'0001'0000'1001'0000'0000'0001'1010
    // 0x01'09'00'1A

    std::vector<uint8_t> expected_bytes = {0x1A, 0x00, 0x09, 0x01};
    std::string expected_output_string(expected_bytes.begin(), expected_bytes.end());

    assembler.process(code_stream, binary_output, false);

    ASSERT_EQ(binary_output.str(), expected_output_string);
}