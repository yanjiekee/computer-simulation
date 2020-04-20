.data 

.text
main:	.frame	$fp,40,$31		# vars= 24, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
 	addiu	$sp,$sp,-40
	sw	$fp,36($sp)
	move	$fp,$sp
	li	$2,4
	sw	$2,8($fp)
	movz	$31,$31,$0
	li	$2,10
	sw	$2,12($fp)
	move	$2,$0
	move	$sp,$fp
	lw	$fp,36($sp)
	addiu	$sp,$sp,40
	j	$31
	nop