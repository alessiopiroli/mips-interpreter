llo $a1, 10000
begin:
trap print_int
addi $a0, $a0, 1
bne $a0, $a1, begin
trap exit