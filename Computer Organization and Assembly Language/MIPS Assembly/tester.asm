   .text

main:
# Create stack frame using calling convention
	addi	$sp,$sp,-12		# Stack frame is 32 bytes long
	sw	$ra,4($sp)		# Save return address
#	sw	$fp,16($sp)		# Save old frame pointer
#	addi	$fp,$sp,28		# Set up frame pointer

# Compute 10!
	li	$a0,4			# Put argument (10) in $a0
	jal	fact			# Call factorial function

# Output result
	add	$a0, $v0, $zero	# Load sum of inupt numbers into $a0
	li	$v0, 1			# Load 1=print_int into $v0
	syscall				# Output the prompt via syscall

# Remove Stack Frame
	lw	$ra,4($sp)		# Restore return address
#	lw	$fp,16($sp)		# Restore frame pointer
	addi	$sp,$sp,12		# Pop stack frame

# Exit
	li	$v0, 10			# exit
	syscall


# Factorial function to compute n!
fact:
# Create stack frame
	addi	$sp, $sp, -12		# Pop stack
	sw	$ra,4($sp)		# Save return address
#	sw	$fp,16($sp)		# Save frame pointer
#	addi	$fp,$sp,28		# Set up frame pointer

	sw	$a0,0($sp)		# Save argument (n)

# See if we need recursive step
	lw	$v0,0($sp)		# Load n
	bgtz	$v0,L2			# Branch if n > 0
	li	$v0,1			# Return 1 if n = 0
	j	L1			# Jump to code to return

# Compute (n-1)!
L2:
	lw	$v1,0($sp)		# Load n
	addi	$v0,$v1,-1		# Compute n - 1
	move	$a0,$v0		# Move value to $a0
	jal	fact			# Call factorial function

	lw	$v1,0($sp)		# Load n
	mul	$v0,$v0,$v1		# Compute (n-1)*n = n!

# Remove Stack Frame and return
L1:					# Result is in $v0
	lw	$ra, 4($sp)		# Restore $ra
#	lw	$fp, 16($sp)		# Restore $fp
	addiu	$sp, $sp, 12		# Pop stack
	jr	$ra			# Return to caller
