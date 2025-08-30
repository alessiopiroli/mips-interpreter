#include "gtest/gtest.h"
#include "assembler.hpp"

class LoadStoreTest : public ::testing::Test {
protected:
    Assembler assembler;
};

TEST_F(LoadStoreTest, LwTest) {
    std::string assembly_code = "lw $t1, 8($t0)";
    std::stringstream code_stream(assembly_code);
    std::stringstream binary_output;

    // opcode = 100011
    // rs = $t0 = 8 = 01000
    // rt = $t1 = 9 = 01001
    // immediate = 8 = 0000'0000'0000'1000
    // instruction
    // 100011'01000'01001'0000000000001000
    // 1000'1101'0000'1001'0000'0000'0000'1000
    // 0x8D'09'00'08

    std::vector<uint8_t> expected_machine_code = {
        0x08, 0x00, 0x09, 0x8D
    };

    std::string expected_output_str(expected_machine_code.begin(), expected_machine_code.end());

    assembler.process(code_stream, binary_output, false);

    ASSERT_EQ(binary_output.str(), expected_output_str);
}