#include "gtest/gtest.h"
#include "assembler.hpp"

class TrapTest : public ::testing::Test {
protected:
    Assembler assembler;
};

TEST_F(TrapTest, TrapOpTest) {
    std::string assembly_code = "trap exit";
    std::stringstream code_stream(assembly_code);
    std::stringstream binary_output;

    // opcode = 011010
    // immediate = 5 = 00000000000000000000000101
    // Instruction
    // 011010'00000000000000000000000101
    // 0110'1000'0000'0000'0000'0000'0000'0101
    // 0x68'00'00'05

    std::vector<uint8_t> expected_machine_code = {
        0x05, 0x00, 0x00, 0x68
    };

    std::string expected_output_str(expected_machine_code.begin(), expected_machine_code.end());

    assembler.process(code_stream, binary_output, false);

    ASSERT_EQ(binary_output.str(), expected_output_str);
}