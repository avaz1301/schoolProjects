

###############################################################################


###############################################################################
.data
PROMPT1:  .asciiz "Please enter an integer between 10 and 20: "
PROMPT2:  .asciiz "Please enter a postive number: "
PROMPT3:  .asciiz "Enter a seguence of 12 integers one by one."
PROMPT4:  .asciiz "You entered: "
array:    .word   0:12
n:        .word 0
.text
main:
START:
   la $a0, PROMPT1                # Loads the PROMPT string into $a0.
   li $v0, 4                     # Loads $a0(PROMPT) into $v0 off the stack.
   syscall   
   
   li $v0, 5                     # Load immediate: reads in input value(CONSTANT) into $v0.OPCODE:5
   syscall                       #
   move $t0, $v0
   blt $t0, 20, NEXT
   j START
NEXT:
   blt $t0, 10, START      
   blt $t0, 15, CASE1
   j CASE2
CASE1:
   la $a0, PROMPT2                # Loads the PROMPT string into $a0.
   li $v0, 4                     # Loads $a0(PROMPT) into $v0 off the stack.
   syscall 
   
   li $v0, 5                     # Load immediate: reads in input value(CONSTANT) into $v0.OPCODE:5
   syscall                       #
   move $v0, $t1 
   blt $t1, $zero, CASE1
   move $a0, $t1
   jal func
   move $s1,$v0
   j PRINT1
###############################################################################  
CASE2:
   la $a0, PROMPT3                # Loads the PROMPT string into $a0.
   li $v0, 4                     # Loads $a0(PROMPT) into $v0 off the stack.
   syscall
   la $t3, array 
   li $t4,0     #$t3 holds the address of the array[12]
	   
ARRAY:
   beq $t4, 12, PRINTARRAY
   li $v0, 5                     # Load immediate: reads in input value(CONSTANT) into $v0.OPCODE:5
   syscall 
   move $s2,$v0
           
   mul $t5, $t4,4    #off set is i*4
   add $t6, $t5, $t3 #$t6 hold address of array[1]
   sw $s0,($t6)
 
   move $a0, $s2              #MOVES THE FINAL ANSWER FROM REGISTER $t2 INTO $a0.
   li $v0, 1                  #print_int>>>>>PRINTS OUT THE INTEGER ANSWER TO THE USER PRECEDED BY "The answer is:"
   syscall            
   add $t4, $t4, 1
   j ARRAY
   
PRINTARRAY:
   la $a0, PROMPT4                # Loads the PROMPT string into $a0.
   li $v0, 4                     # Loads $a0(PROMPT) into $v0 off the stack.
   syscall
   
PRINTLOOP:
   add $t6, $t6, -4   
   move $a0, $t7             #MOVES THE FINAL ANSWER FROM REGISTER $t2 INTO $a0.
   li $v0, 1                  #print_int>>>>>PRINTS OUT THE INTEGER ANSWER TO THE USER PRECEDED BY "The answer is:"
   syscall
   
   j EXIT
.end main
   
   
   
   

PRINT1:
  
   move $a0, $s1              # Moves the value of $t4 from $t4 into $a0.
   li $v0, 1                     # Loads $a0(CONSTANT) into $v0 off the stack.
   syscall    
EXIT:                            # EXIT label
   li $v0, 10                    # OPCODE:10 causes program to exit(exit termination)
   syscall       
################################################################################


###########################################################################
func: 
   addi $sp,$sp,-8
   sw $ra, 0($sp)
   sw $s0, 4($sp)
   
   move $v0, $a0
   li $v0, 10
   beq $a0, $zero, done 
   beq $a0, 1, done ## (n-1)*FUNC(n-1)+n
   
   move $s0, $a0
   addi $a0, $a0,-1
   jal func
   lw $s0, 4($sp)
   move $a0, $s0
   add $t2, $s0, -2
   mul $v0, $t2, $v0
   add $v0, $v0, $s0
done:   
   lw $ra, 4($sp)
   addi $sp,$sp,8
   jr $ra

