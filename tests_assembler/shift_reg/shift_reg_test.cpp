#include "gtest/gtest.h"
#include "assembler.hpp"

class ShiftRegTest : public ::testing::Test {
protected:
    Assembler assembler;
};

TEST_F(ShiftRegTest, SllvTest) {
    std::string assembly_code = "sllv $t0, $t1, $t2";
    std::stringstream code_stream(assembly_code);
    std::stringstream binary_output;

    // opcode = 000000
    // rs = $t2 = 01010
    // rt = $t1 = 01001
    // rd = $t0 = 01000
    // shamt = 00000
    // funct = 000100
    // Instruction
    // 000000'01010'01001'01000'00000'000100
    // 0000'0001'0100'1001'0100'0000'0000'0100
    // 0x01'49'40'04

    std::vector<uint8_t> expected_machine_code = {
        0x04, 0x40, 0x49, 0x01
    };

    std::string expected_output_str(expected_machine_code.begin(), expected_machine_code.end());

    assembler.process(code_stream, binary_output, false);

    ASSERT_EQ(binary_output.str(), expected_output_str);
}