###########################################################################
# RECURSION AND ARRAY PRINTING                                             #
# ANGELO ZAMUDIO                                                           #
# LAST MODIFIED: 5/23/14                                                   #
# ZAMUDIO_h2_1.asm                                                         #
#                                                                         #
###########################################################################
# The purpose of this program is to preform one of either 2 tasks.        # 
# After asking user for a number 10<k<15                                  #
# 1)if 10<=k<15                                                           #
#   we ask user for second number, n, to preform recursion on             #
#   EX: N=4, FUNCT(4)=14.......N=6, FUNCT(6)=194                          #
# 2)if 15<=K2<=20                                                         #
#   we ask user to input 12 numbers to be put into an array               #
#   the array is the output back to the user                              #
# We also have to make sure the program loops back to the start           #
# and ask the user to keep inputing new numbers. If the user              #
# wishes to exit the program we prompt then to enter 0 to                 #
# terminate the program.                                                  #
###########################################################################
# REGISTERS USED:                                                          #
# $t0=k..................$t4=stack address  ......... $v0=funct(n-1)      #
# $t1=n..................$t5=array element value .....$v1=n within funct  #
# $t2=input counter......$t6=(n-2) within funct.......$sp=stack pointer   #
# $t3=array input........$a0=argument ................$ra=return address  #
# $s1=return value from funt(n).......................................    #
###########################################################################


.data
PROMPT1:  .asciiz "Please enter an integer between 10 and 20: "
PROMPT2:  .asciiz "Please enter a postive number: "
RESULT:   .asciiz "The result is: "
PROMPT3:  .asciiz "Enter a sequence of 12 integers one by one. \n"
NEWLINE:  .asciiz "\n"
PROMPT4:  .asciiz "You entered: "
PROMPT5:  .asciiz "Your array holds: "   
retry:    .asciiz "Please try other numbers, if you wish to exit enter 0."
###########################################################################
.text
START:
   la $a0, PROMPT1               # asks user to enter k 
   li $v0, 4                     # OPCODE 4=print_string
   syscall   
   li $v0, 5                     # OPCODE 5=read_int
   syscall                       # reads in user input k
   move $t0, $v0                 # $t0=k
   beq $t0, $zero,EXIT           # branch to exit if k=0
   blt $t0, 21, NEXT             # if k<21 branch to NEXT
   j START                       # else jump to START to try again

NEXT:
   blt $t0, 10, START            # if k<10 branch to START to try again
   blt $t0, 15, CASE1            # if k<15 the branch to CASE1
   j CASE2                       # else jump to CASE2

CASE1:
   la $a0, PROMPT2               # asks user to input a postive n.
   li $v0, 4                     # OPCODE 4=print_string
   syscall   
   li $v0, 5                     # OPCODE 5=read_int
   syscall                       # reads in user input for n
   move $v0, $t1                 # St1=n
   blt $t1, $zero, CASE1         # if n<0 branch to CASE! to try again

# Create stack  
   addi	$sp,$sp,-12		# allocate stack space
   sw	$ra,4($sp)		# save return address to the stack
   move	$a0,$t1			# move argument, n, into $a0
   jal	funct            	# call function
   move	$s1, $v0                # move the return value into $s0
# Remove Stack 
   addi	$sp,$sp,32		# reallocate stack space
   j PRINT                      # jump to PRINT
   
PRINT:
   la $a0, RESULT               # Loads RESULT string into $a0.
   li $v0, 4                    # OPCODE 4=print_string
   syscall
   move $a0, $s1                # Move the return value into $a0 to be printed		
   li $v0, 1                    # OPCODE 1=print_int.
   syscall
   la $a0, NEWLINE              # Loads NEWLINE into $a0 
   li $v0, 4                    # OPCODE 4=print_string  
   syscall  
   j RETRY                      # jump to RETRY
       
CASE2: 
   la $a0, PROMPT3              # Loads PROMPT3 asks user to input 12 numbers  
   li $v0, 4                    # OPCODE 4=print_string
   syscall
   li $t2,0                     # $t2=input counter=0
   addi $sp, $sp, -48           # allocate stack space
   la $t4, 0($sp)               # $t4 has address of 0($sp)

inputLOOP:
   beq $t2, 12,RESETCOUNTER     # if input counter=12 branch to RESETCOUNTER
   li $v0, 5                    # OPCODE 5=read_int
   syscall                      # reads in user input for array
   move $t3, $v0                # moves user input into $t3
   la $a0, PROMPT4              # loads PROMPT4 tells user they entered...
   li $v0, 4                    # OPCODE 4=print_string
   syscall
   move $a0, $t3              	# moves user input into $a0	
   li $v0, 1                    # OPCODE 1=print_int 
   syscall                      # show user the number they input
   la $a0, NEWLINE              # loads NEWLINE into $a0
   li $v0, 4                    # OPCODE 4=print_string
   syscall
   sw  $t3, ($t4)               # stores user input into current address in $t4
   add $t4,$t4,4                # points to next address by adding 4 to $t4
   add $t2, $t2, 1              # increase input counter by 1
   j inputLOOP                  # jump to inputLOOP

RESETCOUNTER:
   li $t2,0                     # reset input counter to 0
   la $a0, PROMPT5              # loads PROMPT5 thells user thier array hold... 
   li $v0, 4                    # OPCODE 4=print_string  
   syscall
   la $a0, NEWLINE              # loads NEWLINE into $a0
   li $v0, 4                    # OPCODE 4=print_string
   syscall
   add $t4,$t4,-4               # since current address at $t4 point to address
                                # after last element, subtract 4 to get address 
                                # of last element
PRINTARRAY:
   beq $t2, 12,RETRY            # if counter=12 branch to RETRY
   lw $t5,($t4)                 # loads value in current address in $t4 into $t5
   move $a0, $t5                # moves aray value into $a0
   li $v0,1                     # OPCODE 1=print_int
   syscall
   add $t2, $t2, 1              # increase counter by 1
   add $t4,$t4,-4              	# move down the array by subracting 4 from 
                                # address in $t4	
   la $a0, NEWLINE              # loads NEWLINE into $ao
   li $v0, 4                    # OPCODE 4=print_string 
   syscall  
   j PRINTARRAY                 # jump to PRINTARRAY
   
RETRY:
   la $a0, retry                # loads retry asks user to try more #'s or
                                # enter 0 to exit program
   li $v0, 4                    # OPCODE 4=print_string 
   syscall 
   la $a0, NEWLINE              # loads NEWLIN into $a0
   li $v0, 4                    # OPCODE 4=print_string 
   syscall   
   j START                      # jump back to START
   
EXIT:
   addi $sp,$sp,48              # reallocate space set aside in stack
   li $v0, 10                   # OPCODE 10=exit
   syscall                      # exits the program
    
###########################################################################
funct:
# Create stack frame
   addi	$sp,$sp,-12		# allocate stack space
   sw $ra,4($sp)                # store original return address into the stack
   sw $a0,0($sp)		# store orignal arg value into the stack
# See if we need recursive step
   lw $v0,0($sp)                # load n into $v0
   bne $v0,1,recur              # if n!=1 branch to recur
   li $v0, 10                   # else load return value:10 into $v0
   j done                       # jump to done
recur:
   lw $v0,0($sp)                # load original n from the stack to $v0
   addi $v0,$v0,-1              # get n-1
   move $a0,$v0                 # move n-1 into $a0 as arg for recursive call
   jal funct                    # recursive call funct(n-1)
                                # $v0 hold funt(n-1)
   lw $v1, 0($sp)               # load original n from stack into $v1
   add $t6, $v1, -2             # $t6=n-2
   mul $v0, $v0, $t6            # multiply funct(n-1)*(n-2)
   add $v0,$v0,$v1              # add n to [funct(n-1)*(n-2)] and place in $v0
done:
   lw $ra, 4($sp)		# Restore original $ra
   addi	$sp, $sp, 12		# reallocate stack space
   jr $ra			# jump to register $ra (address of caller)
      


