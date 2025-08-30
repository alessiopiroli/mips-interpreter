#include "gtest/gtest.h"
#include "assembler.hpp"

class AssemblerArithLogicTest : public ::testing::Test {
protected:
    Assembler assembler;
};

TEST_F(AssemblerArithLogicTest, AddTest) {
    std::string assembly_code = "add $t2, $t0, $t1";
    std::stringstream code_stream(assembly_code);
    std::stringstream binary_output;

    // opcode = 000000
    // rs = $t0 = reg. 8 = 01000
    // rt = $t1 = reg. 9 = 01001
    // rd = $t2 = reg. 10 = 01010
    // shamt = 00000
    // funct = 100000
    // Instruction
    // 000000'01000'01001'01010'00000'100000
    // 0000'0001'0000'1001'0101'0000'0010'0000
    // 0x01095020

    std::vector<uint8_t> expected_bytes = {0x20, 0x50, 0x09, 0x01};
    std::string expected_output_string(expected_bytes.begin(), expected_bytes.end());

    assembler.process(code_stream, binary_output, false);

    ASSERT_EQ(binary_output.str(), expected_output_string);
}