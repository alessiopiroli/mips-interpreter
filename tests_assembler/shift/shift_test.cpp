#include "gtest/gtest.h"
#include "assembler.hpp"

class ShiftTest : public ::testing::Test {
protected:
    Assembler assembler;
};

TEST_F(ShiftTest, SllTest) {
    std::string assembly_code = "sll $t0, $t1, 4";
    std::stringstream code_stream(assembly_code);
    std::stringstream binary_output;

// opcode = 000000
    // rt = $t1 = reg. 9 = 01001
    // rd = $t0 = reg. 8 = 01000
    // shamt = 4 = 00100 
    // funct = 000000
    // Instruction
    // 000000'00000'01001'01000'00100'000000
    // 0000'0000'0000'1001'0100'0001'0000'0000
    // 0x00'09'41'00

    std::vector<uint8_t> expected_machine_code = {
        0x00, 0x41, 0x09, 0x00
    };

    std::string expected_output_str(expected_machine_code.begin(), expected_machine_code.end());

    assembler.process(code_stream, binary_output, false);

    ASSERT_EQ(binary_output.str(), expected_output_str);
}