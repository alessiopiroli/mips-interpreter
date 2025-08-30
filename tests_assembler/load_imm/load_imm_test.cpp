#include "gtest/gtest.h"
#include "assembler.hpp"

class LoadImmTest : public ::testing::Test {
protected:
    Assembler assembler;
};

TEST_F(LoadImmTest, LloTest) {
    std::string assembly_code = "llo $t0, 65535";
    std::stringstream code_stream(assembly_code);
    std::stringstream binary_output;

    // opcode = 011000
    // rs = 00000
    // rt = $t0 = reg. 8 = 01000
    // immediate = 0xFFFF = 1111'1111'1111'1111
    // Instruction
    // 011000'00000'01000'1111111111111111
    // 0110'0000'0000'1000'1111'1111'1111'1111
    // 0x60'08'FF'FF

    std::vector<uint8_t> expected_machine_code = {
        0xFF, 0xFF, 0x08, 0x60
    };

    std::string expected_output_str(expected_machine_code.begin(), expected_machine_code.end());

    assembler.process(code_stream, binary_output, false);

    ASSERT_EQ(binary_output.str(), expected_output_str);
}