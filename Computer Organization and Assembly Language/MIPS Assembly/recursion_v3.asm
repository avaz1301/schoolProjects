.data
PROMPT1:  .asciiz "Please enter an integer between 10 and 20: "
PROMPT2:  .asciiz "Please enter a postive number: "
array:    .word   0:12
.text
START:
   la $a0, PROMPT1                # Loads the PROMPT string into $a0.
   li $v0, 4                     # Loads $a0(PROMPT) into $v0 off the stack.
   syscall   
   
   li $v0, 5                     # Load immediate: reads in input value(CONSTANT) into $v0.OPCODE:5
   syscall
                          #
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
   move $t1, $v0 
   blt $t1, $zero, CASE1
   jal FUNC
   move $t3,$v0
   j PRINT1
   
FUNC:
   move $a0, $t1
   beq $a0, $zero,RETURN
   bne $a0,1, ELSE
RETURN:
   li $v0, 10
   jr $ra
ELSE:
   addi $sp, $sp, -8
   sw $ra, 4($sp)
   sw $a0, 0($sp)
  # addi $s0, $a0, -2
   #la $s1, $a0
   addi $a0,$a0,-1
   jal FUNC
   lw $a0,0($sp)
   addi $s0, $a0, -2
   mul $v0, $s0, $v0
   add $v0, $v0, $a0
   lw $ra, 4($sp)
   addi $sp, $sp, 8
   jr $ra
   
   
CASE2:
  j EXIT

PRINT1:  
   move $a0, $t3              # Moves the value of $t4 from $t4 into $a0.
   li $v0, 1                     # Loads $a0(CONSTANT) into $v0 off the stack.
   syscall    
EXIT:                            # EXIT label
   li $v0, 10                    # OPCODE:10 causes program to exit(exit termination)
   syscall     
   
   
   
   
   
   
   