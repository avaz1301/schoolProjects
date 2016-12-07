#########################################################
#RECURSION AND ARRAY PRINTING
#ANGELO ZAMUDIO
#LAST MODIFIED: 5/23/14
#ZAMUDIO_h2_1.asm
#
#
#
#
#
#
#
#
##########################################################
.data
PROMPT1:  .asciiz "Please enter an integer between 10 and 20: "
PROMPT2:  .asciiz "Please enter a postive number: "
RESULT:   .asciiz "The result is: "
PROMPT3:  .asciiz "Enter a sequence of 12 integers one by one. \n"
NEWLINE:  .asciiz "\n"
PROMPT4:  .asciiz "You entered: "
PROMPT5:  .asciiz "Your array holds: "   
retry:    .asciiz "Please try other numbers, if you wish to exit enter 0."
###########################################################
.text
START:
   la $a0, PROMPT1                # Loads the PROMPT string into $a0.
   li $v0, 4                     # Loads $a0(PROMPT) into $v0 off the stack.
   syscall   
   
   li $v0, 5                     # Load immediate: reads in input value(CONSTANT) into $v0.OPCODE:5
   syscall                       #
   move $t0, $v0
   beq $t0, $zero,EXIT
   blt $t0, 20, NEXT
   j START
NEXT:
   blt $t0, 10, START      
   blt $t0, 15, CASE1
   j CASE2
   ################   
CASE1:
   la $a0, PROMPT2                # Loads the PROMPT string into $a0.
   li $v0, 4                     # Loads $a0(PROMPT) into $v0 off the stack.
   syscall   
   li $v0, 5                     # Load immediate: reads in input value(CONSTANT) into $v0.OPCODE:5
   syscall                       #
   move $v0, $t1 
   blt $t1, $zero, CASE1
   ################   
   addi	$sp,$sp,-12		# Stack frame is 32 bytes long
   sw	$ra,4($sp)		# Set up frame pointer
# Compute 10!
   move	$a0,$t1			# Put argument (10) in $a0
   jal	funct			# Call factorial function

   move	$s1, $v0                # Load sum of inupt numbers into $a0			# Output the prompt via syscall
# Remove Stack Frame
  # lw	$ra,4($sp)		# Restore return address
   addi	$sp,$sp,32		# Pop stack frame
   j PRINT
   ##############
PRINT:
   la $a0, RESULT                # Loads the PROMPT string into $a0.
   li $v0, 4                     # Loads $a0(PROMPT) into $v0 off the stack.
   syscall
   move $a0, $s1              # Moves the value of $t4 from $t4 into $a0.		
   li $v0, 1                     # Loads $a0(CONSTANT) into $v0 off the stack.
   syscall
   la $a0, NEWLINE               
   li $v0, 4                     
   syscall  
   j RETRY
   ################    
CASE2: 
   la $a0, PROMPT3                
   li $v0, 4                     
   syscall
   li $t2,0                  #input counter=0
   addi $sp, $sp, -48
   la $t4, 0($sp)              #$t4 has address of 0($sp)
inputLOOP:
   beq $t2, 12,RESETCOUNTER  
   li $v0, 5                    
   syscall
   move $t3, $v0
   la $a0, PROMPT4               
   li $v0, 4                     
   syscall
   move $a0, $t3              		
   li $v0, 1                     
   syscall
   la $a0, NEWLINE               
   li $v0, 4                     
   syscall
   sw  $t3, ($t4)
   add $t4,$t4,4   
   add $t2, $t2, 1
   j inputLOOP 
RESETCOUNTER:
   li $t2,0
   la $a0, PROMPT5               
   li $v0, 4                     
   syscall
   la $a0, NEWLINE               
   li $v0, 4                     
   syscall
   add $t4,$t4,-4
PRINTARRAY:
   beq $t2, 12,RETRY   
   lw $t5,($t4)
   move $a0, $t5
   li $v0,1
   syscall
   add $t2, $t2, 1
   add $t4,$t4,-4              		
   la $a0, NEWLINE               
   li $v0, 4                     
   syscall  
   j PRINTARRAY
   ################
RETRY:
   la $a0, retry               
   li $v0, 4                     
   syscall 
   la $a0, NEWLINE               
   li $v0, 4                     
   syscall   
   j START
EXIT:
   addi $sp,$sp,48              
   li $v0, 10               # OPCODE:10 causes program to exit(exit termination)
   syscall
    
###########################################################################
funct:
# Create stack frame
	addi	$sp,$sp,-12		# Stack frame is 32 bytes long
	sw	$ra,4($sp)
	sw	$a0,0($sp)			# Save return address
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
        add $t6, $v1, -2
        mul $v0, $v0, $t6
        add $v0,$v0,$v1
	
done:
        lw	$ra, 4($sp)		# Restore $ra
	addi	$sp, $sp, 12		# Pop stack
	jr	$ra			
      


