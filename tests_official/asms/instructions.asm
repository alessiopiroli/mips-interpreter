lhi $a0, 1
llo $a0, 0
trap print_int
sll $a0, $a0, 1
trap print_int
srl $a0, $a0, 2
trap print_int
lhi $a0, 65535
llo $a0, 65535
trap print_int
sra $a0, $a0, 1
trap print_int
srl $a0, $a0, 1
trap print_int
lhi $a0, 0
trap print_int
sra $a0, $a0, 1
trap print_int
llo $a1, 1
sllv $a0, $a0, $a1
trap print_int
srlv $a0, $a0, $a1
trap print_int
lhi $a0, 65535
llo $a0, 65535
trap print_int
srav $a0, $a0, $a0
trap print_int
la $a0, label1
trap print_int
jr $a0
trap exit
label1:
trap print_int
la $a0, label2
trap print_int
jalr $a0
trap exit
label2:
trap print_int
addi $a0, $ra, 0
trap print_int
llo $a0, 0
lhi $a0, 1
trap print_int
mthi $a0
lhi $a0, 0
mfhi $a0
trap print_int
llo $a0, 1234
lhi $a0, 5678
trap print_int
mtlo $a0
lhi $a0, 0
mflo $a0
trap print_int
llo $a0, 65530
lhi $a0, 65535
llo $a1, 65535
lhi $a1, 65535
mult $a0, $a1
mflo $a0
trap print_int
mfhi $a0
trap print_int
llo $a0, 65530
lhi $a0, 65535
llo $a1, 65535
lhi $a1, 65535
multu $a0, $a1
mflo $a0
trap print_int
mfhi $a0
trap print_int
llo $a0, 1234
lhi $a0, 0
llo $a1, 65526
lhi $a1, 65535
div $a0, $a1
mflo $a0
trap print_int
mfhi $a0
trap print_int
llo $a0, 1234
lhi $a0, 0
llo $a1, 65526
lhi $a1, 65535
divu $a0, $a1
mflo $a0
trap print_int
mfhi $a0
trap print_int
llo $a1, 10
lhi $a1, 0
llo $a2, 2
lhi $a2, 0
add $a0, $a1, $a2
trap print_int
llo $a1, 9
addu $a0, $a1, $a2
trap print_int
sub $a0, $a1, $a2
trap print_int
llo $a1, 8
subu $a0, $a1, $a2
trap print_int
llo $a1, 3
llo $a2, 7
and $a0, $a1, $a2
trap print_int
or $a0, $a1, $a2
trap print_int
xor $a0, $a1, $a2
trap print_int
nor $a0, $a1, $a2
trap print_int
lhi $a1, 65535
slt $a0, $a1, $a2
trap print_int
slt $a0, $a2, $a1
trap print_int
sltu $a0, $a1, $a2
trap print_int
sltu $a0, $a2, $a1
trap print_int
llo $a0, 0
lhi $a0, 0
trap print_int
addi $a1, $a0, 0
addi $a0, $a1, 0
trap print_int
beq $a0, $a1, label3
j end
label3:
bne $a0, $a1, end
blez $a0, label4
j end
label4:
llo $a1, 1
bgtz $a1, label5
j end
label5:
addiu $a0, $a0, 1
trap print_int
addiu $a0, $a0, 6
andi $a0, $a0, 11
trap print_int
ori $a0, $a0, 17
trap print_int
xori $a0, $a0, 7
trap print_int
la $a1, data
lb $a0, 0 ($a1)
trap print_int
lbu $a0, 0 ($a1)
trap print_int
lh $a0, 0 ($a1)
trap print_int
lhu $a0, 0 ($a1)
trap print_int
lh $a0, 4 ($a1)
trap print_int
lw $a0, 0 ($a1)
trap print_int
lb $a0, 0 ($a1)
trap print_int
llo $a0, 259
sb $a0, 8 ($a1)
lbu $a0, 8 ($a1)
trap print_int
llo $a0, 1
lhi $a0, 1
trap print_int
sh $a0, 8 ($a1)
lhu $a0, 8 ($a1)
trap print_int
lhi $a0, 32
sw $a0, 4 ($a1)
lw $a0, 4 ($a1)
trap print_int
jal label7
j end
label7:
addi $a0, $ra, 0
trap print_int
la $a1, strings
lbu $a0, 0 ($a1)
trap print_character
la $a0, strings
trap print_string
llo $a0, 10
trap print_character
end:
trap exit
data:
.word 255
.word 65535
.byte 123
.byte 111
strings:
.asciiz "Hello, World!"