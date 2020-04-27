.data

.text
main:	addi $s0 $zero 1
		addi $s1 $zero 99
L6:		slt $t0 $s0 $s1
		beq $t0 $zero exitL6
		addi $sp $sp -8
		sw $s0 0($sp)
		sw $s1 4($sp)
		add $a0 $s0 $zero
		jal square
		lw $s1 4($sp)
		lw $s0 0($sp)
		addi $sp $sp 8
		addi $s0 $s0 1
		j L6
exitL6:	addi $v0 $zero 10
	syscall
square:	addi $v0 $zero 0
		addi $t1 $zero 0
L5:		slt $t3 $t1 $a0
		beq $t3 $zero exitL5
		add $v0 $v0 $a0
		addi $t1 $t1 1
		j L5
exitL5:	
addi $sp $sp -8
	sw $a0 0($sp)
	add $a0 $v0 $zero
	sw $v0 4($sp)
	li $v0 1
	
	syscall
	li $v0 11
	li $a0 10	# newline
	syscall
	lw $v0 4($sp)
	lw $a0 0($sp)
	addi $sp $sp 8
		jr $ra
