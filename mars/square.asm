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
exitL6:	terminate
square:	addi $v0 $zero 0
		addi $t1 $zero 0
L5:		slt $t3 $t1 $a0
		beq $t3 $zero exitL5
		add $v0 $v0 $a0
		addi $t1 $t1 1
		j L5
exitL5:	sw $v0 0($mp)
		addi $mp $mp 4
		jr $ra
