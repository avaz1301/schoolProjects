# FOR LOOP ADDITION PROGRAM
# ANGELO ZAMUDIO
# LAST MODIFIED: 4/24/14
# ZAMUDIO_h1_2.s

# THE PURPOSE OF THIS PROGRAM IS TO PREFORM AN ADDITON OPERATION
# 30 TIMES. THIS IS TO BE DONE THROUGH THE USE OF A FOR LOOP WITH VALUE
# J STARTING AT ZERO UNTIL J<30. THE USER IS FIRST ASKED TO INPUT A NUMBER
# WHICH WILL BE THE CONSTANT THAT THE INCREMENTED J WILL BE ADDED TO. FINALLY
# AFTER J HAS BEEN ADDED TO THE CONSTANT THE PROGRAM PRINTS OUT
# "FOR J EQUAL " J " TOTAL EQUALS " TOTAL, THEN IT MOVES DOWN TO THE NEXT LINE 
# TO PRINT THE NEXT ITERATION OF THE ADDITON.

#$t0= hold the value of CONSTANT..................... $t4= TOTAL, hold value of J+CONSTANT
#$t1= hold the value of J............................ $a0
#$t2= is the upper bound of the for loop............. $v0
#$t3= hold the truth value of slt (1 or 0)...........

    
# C-PSEUDO-CODE
# for(int j=0; j<30; j++){ 
#     Total=j+constant; 
#     Println(“for j equal, ” +j +“total equal ” + Total); 
# } 

.data
PROMPT:  .asciiz "Please enter a number to be set as a constant: "
string1: .asciiz "For j equal,"
string2: .asciiz " total equals "
newline: .asciiz " \n"

.text
   la $a0, PROMPT                # Loads the PROMPT string into $a0.
   li $v0, 4                     # Loads $a0(PROMPT) into $v0 off the stack.
   syscall                       # Prints out PROMPT string to the user.OPCODE:4
                                 #
   li $v0, 5                     # Load immediate: reads in input value(CONSTANT) into $v0.OPCODE:5
   syscall                       #
   move $t0, $v0                 # constant = $t0, moves the input value from $v0 into $t0. 
                                 #
   li $t1, 0                     # j = $t1, Load imm. place the value 0 into register $t1.
   li $t2, 30                    # upper bound = $t2, Load imm. place the value 30 into register $t2.
                                 # 
FORLOOP:                         # Beginning of FOR LOOP.
   slt $t3, $t1, $t2             # $t3 == holds truth value of ($t1 < $t2)
   beq $t3, 1, CONTINUE          # if $t3=1(TRUE), j<30, go to label Continue
   beq $t3, $zero, EXIT          # if $t3=$zero(FALSE), j>30, if this is the case we exit the for loop.
CONTINUE:                        # continue label
   add $t4, $t0, $t1             # TOTAL=CONSTANT+J, adds value in register $t0 and $t1 and inputs sum in $t4.
# prints "For j equal, "   
   la $a0, string1               # Loads address of string1 into register $a0.
   li $v0, 4                     # Loads $a0(string1) into $v0 off the stack. 
   syscall                       # Prints out string1. OPCODE:4
# prints j   
   move $a0, $t1                 # Moves the value of J from $t1 into $a0.
   li $v0, 1                     # Loads $a0(J) into $v0 off the stack. 
   syscall                       # Prints out j. OPCODE:1
# prints " total equals "
   la $a0, string2               # Loads address of string2 into register $a0.
   li $v0, 4                     # Loads $a0(string2) into $v0 off the stack.
   syscall                       # Prints out string2. OPCODE:4
# prints $t4>>>TOTAL
   move $a0, $t4                 # Moves the value of $t4 from $t4 into $a0.
   li $v0, 1                     # Loads $a0(CONSTANT) into $v0 off the stack.
   syscall                       # Prints out $t4(CONSTANT). OPCODE:1
# moves to next line to print next solution
   la $a0, newline               # Loads address of newline into register $a0
   li $v0, 4                     # Loads $a0(newline) into $v0 off the stack.
   syscall                       # Prints out a new line. OPCODE:4
# increses value of j by 1 
   addi $t1, $t1,1               # J=J+1, adds 1 to the value in register $t1 and inputs sum back into $t1.
# sends program back to the top of the loop
   j FORLOOP                     # Jumps back to the top of the for loop to repeat the process until it exits.
   
# exits program   
EXIT:                            # EXIT label
   li $v0, 10                    # OPCODE:10 causes program to exit(exit termination)
   syscall                       # 
