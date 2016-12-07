#RECURSION TEST                                             #
#ANGELO ZAMUDIO                                                           #
#LAST MODIFIED: 5/23/14                                                   #
#recursion_test.asm 

.data
.text
     main:
	addi	$sp,$sp,-12		
	sw	$ra,4($sp)		
# Compute 
	li $v0, 5                     
	syscall  
	move $t3,$v0  
	move $a0,$t3			
	jal	funct			
# Output result
	move	$a0, $v0                
	li	$v0, 1			
	syscall				
# Remove Stack Frame		
	addi	$sp,$sp,32		
# Exit
	li	$v0, 10			
	syscall
# function 
funct:
# Create stack frame
	addi	$sp,$sp,-12
	sw	$ra,4($sp)
	sw	$a0,0($sp)			
# See if we need recursive step
	lw $v0,0($sp)
        bne $v0,1,recur
        li $v0, 10
        j done
##############
recur:
        lw $v0,0($sp)
        addi $v0,$v0,-1
        move $a0,$v0
	jal funct     #$v0 hold funt(n-1)
	lw $v1, 0($sp)#has n
        add $t0, $v1, -2
        mul $v0, $v0, $t0
        add $v0,$v0,$v1
	
done:
        lw	$ra, 4($sp)		# Restore $ra
	addi	$sp, $sp, 12		# Pop stack
	jr	$ra			
      



