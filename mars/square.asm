.data

.text
main:
	addi $a0 $zero 5
	jal square
	nop
	addi $v0 $zero 10
	syscall

square:
	addi $v0 $zero 0
	addi $t1 $zero 0

L5:
	slt $t3 $t1 $a0
	beq $t3 $zero exitL5
	add $v0 $v0 $a0
	addi $t1 $t1 1
	j L5

exitL5:
	jr $ra
