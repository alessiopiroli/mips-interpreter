#include "gtest/gtest.h"
#include "assembler.hpp"

class ArithLogicImmTest : public ::testing::Test {
protected:
    Assembler assembler;
};

TEST_F(ArithLogicImmTest, AddiTest) {
    std::string assembly_code = "addi $t1, $t0, 10";
    std::stringstream code_stream(assembly_code);
    std::stringstream binary_output;

    // opcode = 001000
    // $rs = $t0 = reg. 8 = 01000
    // $rd = $t1 = reg. 9 = 01001
    // immediate = 10 = 0000'0000'0000'1010
    // INSTRUCTION
    // 001000'01000'01001'0000'0000'0000'1010
    // 0010'0001'0000'1001'0000'0000'0000'1010
    // 0x21'09'00'0A

    std::vector<uint8_t> expected_bytes = {0x0A, 0x00, 0x09, 0x21};
    std::string expected_output_string(expected_bytes.begin(), expected_bytes.end());

    assembler.process(code_stream, binary_output, false);

    ASSERT_EQ(binary_output.str(), expected_output_string);
}