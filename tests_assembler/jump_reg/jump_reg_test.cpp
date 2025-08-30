#include "gtest/gtest.h"
#include "assembler.hpp"

class JumpTestReg : public ::testing::Test {
protected:
    Assembler assembler;
};

TEST_F(JumpTestReg, JalrTest) {
    std::string assembly_code = "jalr $t0";
    std::stringstream code_stream(assembly_code);
    std::stringstream binary_output;

    // opcode = 000000
    // rs = $t0 = reg. 8 = 01000
    // rt = 00000
    // rd = $ra = reg. 31 = 11111
    // shamt = 00000
    // funct = 001001
    // Instruction
    // 000000'01000'00000'11111'00000'001001
    // 0000'0001'0000'0000'1111'1000'0000'1001
    // 0x01'00'F8'09

    std::vector<uint8_t> expected_machine_code = {
        0x09, 0xF8, 0x00, 0x01
    };

    std::string expected_output_str(expected_machine_code.begin(), expected_machine_code.end());

    assembler.process(code_stream, binary_output, false);

    ASSERT_EQ(binary_output.str(), expected_output_str);
}