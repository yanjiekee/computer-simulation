
main:
	addi $t0 $zero 1000
	add $a0 $zero $t0
	jal primalityTest
	
	addi $s0 $zero 1
	addi $s1 $zero 99
L6:		slt $t0 $s0 $s1
		beq $t0 $zero exitL6
		addi $sp $sp -8
		sw $s0 0($sp)
		sw $s1 4($sp)
		add $a0 $s0 $zero
		jal square
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
		lw $s1 4($sp)
		lw $s0 0($sp)
		addi $sp $sp 8
		addi $s0 $s0 1
		j L6

exitL6:	addi $v0 $zero 10
	syscall

primalityTest:
	add $fp $sp $zero
	sub $sp $sp $t0
	addi $t0 $zero 0
	addi $t1 $a0 1

L1:
	slt $t2 $t0 $t1
	beq $t2 $zero exitL1
	sub $t2 $fp $t0
	add $t3 $zero 1
	sb $t3 0($t2)
	addi $t0 $t0 1
	j L1

exitL1:
	addi $s0 $zero 2

L2:
	addi $sp $sp -12
	sw $a0 8($sp)
	sw $s0 4($sp)
	sw $ra 0($sp)
	add $a0 $s0 $zero
	jal square
	lw $ra 0($sp)
	lw $s0 4($sp)
	lw $a0 8($sp)
	addi $sp $sp 12
	addi $t0 $a0 1
	slt $t1 $v0 $t0
	beq $t1 $zero exitL2

C1:
	sub $t0 $fp $v0
	lb $t1 0($t0)
	beq $t1 $zero exitC1
	# else, initialise for-loop (first iterate and also tweek variable for condition)
	addi $sp $sp -12
	sw $a0 8($sp)
	sw $s0 4($sp)
	sw $ra 0($sp)
	add $a0 $s0 $zero
	jal square
	lw $ra 0($sp)
	lw $s0 4($sp)
	lw $a0 8($sp)
	addi $sp $sp 12
	add $t0 $v0 $zero	# j = i^2
	addi $t1 $a0 1

L3:
	slt $t3 $t0 $t1
	beq $t3 $zero exitL3
	sub $t4 $fp $t0
	addi $t2 $zero 0
	sb $t2 0($t4)
	add $t0 $t0 $s0
	j L3

exitL3:

exitC1:
	addi $s0 $s0 1
	j L2

exitL2:
	addi $t0 $zero 2
	addi $t1 $a0 1

L4:
	slt $t2 $t0 $t1
	beq $t2 $zero exitL4

C2:
	sub $t2 $fp $t0
	lb $t3 0($t2)
	beq $t3 $zero exitC2
	addi $sp $sp -4	# From here to bottom is printing result onto the screen, change to store into memory instead
	sw $a0 0($sp)
	li $v0 1
	add $a0 $t0 $zero
	syscall
	li $v0 11
	li $a0 10	# newline
	syscall
	lw $a0 0($sp)
	addi $sp $sp 4

exitC2:
	addi $t0 $t0 1
	j L4

exitL4:
	lw $t0 range
	add $sp $sp $t0
	jr $ra

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
