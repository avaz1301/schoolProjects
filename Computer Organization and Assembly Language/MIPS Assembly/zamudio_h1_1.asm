# ADDITION PROGRAM 
#ANGELO ZAMUDIO
#LAST MODIFIED: 4/24/14
#ZAMUDIO_h1_1.s

#THE PROGRAM ASKS THE USER TO INPUT TWO NUMBERS. BOTH NUMBERS MUST BE WITHIN 0 AND 20.
#IF THE NUMBERS DO NOT FALL INTO THIS RANGE THE USER WILL E ASKED TO ENTER THE NUMBERS AGAIN. 
#ONCE GIVEN 2 VALID INPUTS THE PROGRAM WILL THEN ADD BOTH INTEGERS AND MULTIPLY THE SUM BY 8.
#THE PROGRAM WILL THEN PRINT OUT THE FINAL RESULT AND ASK THE USER TO INPUT TWO NEW NUMBERS.
#THIS WILL CONTINUE UNTIL THE USER INPUTS THE SENTINEL VALUE OF -10 TO EXIT THE PROGRAM.


# C-PSEUDO-CODE:
#while(input1!=-10||input2!=10){
#   cout<<"please input first number: ";
#   cin>> input1;
#   if(input1<0||input1>20)
#     cout<<"please input a number between 0 and 20: "
#     cin>>input1;
#   cout<<"please input second number: ";
#   cin>>input2;
#   if(input2<0||input2>20)
#      cout<<"please input a number betwwen 0 and 20: ";
#      cin>>input2;
#   int ans= (input1+input2)*8;
#   cout<<"the answer is: " <<ans<<endl;
#   cout<<"enter more numbers or enter -10 to exit."<< endl;  
#}
#return 0;


# $t0= sentiel value(-10).................$s0= the first input number........... $a0= hold argument values
# $t1= sum of the two integers............$s1= the second input number..........
# $t2= product of $t1 and 8...............$vo= hold return values...............

.data
   input1: .asciiz "Please enter first number: "    
   input2: .asciiz "Please enter second number: "   
   retry:  .asciiz "Numbers must be between 0 and 20. Try again or enter -10 to exit.\n "
   answer: .asciiz "The answer is: "
   repeat: .asciiz "\nPlease try more numbers. If you wish to stop enter -10 to exit the program.\n "
.text
NUMBERS:
#FIRST NUMBER
   li $t0, -10                #STORES VALUE OF -10 IN $t1 AS THE SENTINEL VALUE.
   la $a0, input1             #lOADS THE input1 STRING INTO REGISTER $a0.
   li $v0, 4                  #print_string>>>>>PRINTS OUT STRING input1 TO THE USER.
   syscall                    #used to call system services to perform I/O.
   li $v0, 5                  #read_int>>>>>READS IN THE FIRST INPUT VALUE AND STORES IT IN $v0.
   syscall                    #used to call system services to perform I/O.
   move $s0, $v0              #MOVES THE INPUT VALUE FROM $v0 TO $s0.
   beq $s0, $t0, EXIT         #CHECKS IF INPUT 1 WAS THE SENTINEL VALUE(-10) USING BRANCH IF EQUAL TO $t0 THIS IS DONE FIRST TO PREVENT CONFLICT WITH THE NEGATIVE CHECK.
   bgt $s0, 20, RETRY         #CHECKS IF INPUT 1 IS LESS THAN 20 USING BRANCH IF GREATER THAN 20. IF TRUE GO TO RETRY TO INPUT VALID NUMBER
   blt $s0, $zero, RETRY      #CHECKS IF INPUT 1 IS NOT A NEGATIVE NUMBER USING BRANCH IF LESS THAN 0. IF TRUE ALSO TAKES USER TO RETRY TO INPUT A VALID NUMBER.

#SECOND NUMBER
   la $a0, input2             #lOADS THE input2 STRING INTO $a0.
   li $v0, 4                  #print_string>>>>>PRINTS OUT STRING input2 TO THE USER.
   syscall                    #used to call system services to perform I/O.
   li $v0, 5                  #read_int>>>>>READS IN THE SECOND INPUT VALUE AND STORES IT IN REGISTER $v0.
   syscall                    #used to call system services to perform I/O.
   move $s1, $v0              #THIS MOVES THE SECOND INPUT VALUE FROM $v0 TO $s1.
   beq $s1, $t0, EXIT         #CHECKS IF INPUT 2 WAS THE SENTINEL VALUE (-10) USING BRANCH IF EQUAL TO $t0. IF TRUE GO TO EXIT.
   bgt $s1, 20, RETRY         #CHECKS IF INPUT 2 IS LESS THAN 20 USING BRANCH IF GREATER THAN 20. IF TRUE GO TO LABEL RETRY TO INPUT A VALID NUMBER.
   blt $s1, $zero, RETRY      #CHECKS IF INPUT 2 IS NOT A NEGATIVE NUMBER USING BRANCH IF LESS THAN 0. IF TRUE IT ASLO GOES TO RETRY TO INPUT VALID NUMBERS.

#OPERATION (int1 + int2)*8  
   add $t1, $s0, $s1          #ADDS INPUT 1 + INPUT 2 IN REGISTERS $s0 AND $s1 AND STORES SUM IN $t1.
   sll $t2, $t1, 3            #USING SHIFT LEFT LOGICAL TO MULTIPLY THE SUM IN REGISTER $t1>>>>>>>>>> $t1= $s0+$s1  
                              #BY SHIFTING LEFT 3 BITS WHICH IS, 2^3=8.>>>>>>>>>>> $t2= $t1*(2^3)
#PRINT ANSWER  
   la $a0, answer             #LOADS THE answer STRING INTO $a0.
   li $v0, 4                  #print_string>>>>>PRINTS OUT THE STRING answer TO THE USER.
   syscall                    #used to call system services to perform I/O.
   move $a0, $t2              #MOVES THE FINAL ANSWER FROM REGISTER $t2 INTO $a0.
   li $v0, 1                  #print_int>>>>>PRINTS OUT THE INTEGER ANSWER TO THE USER PRECEDED BY "The answer is:"
   syscall                    #used to call system services to perform I/O.

#REPEAT
   la $a0, repeat             #LOADS THE repeat STRING INTO REGISTER $a0.
   li $v0, 4                  #print_string>>>>>PRINTS OUT THE STRING repeat TO THE USER TELL HIM/HER TO EITHER INPUT NEW NUMBERS OR EXIT.
   syscall                    #used to call system services to perform I/O.
   j NUMBERS                  #JUMPS BACK TO THE TOP OF THE PROGRAM LABELED NUMBERS WHICH WILL ALLOW
                              #THE USER TO ENTER A NEW SET OF NUMBERS OR ENTER THE SENTINEL BALUE TO EXIT.

EXIT:   li $v0, 10            #exit>>>>>>>EXITS THE PROGRAM USING A SYSTEM CALL.
        syscall               #used to call system services to perform I/O.
        
        
RETRY:   la $a0, retry        #LOADS THE retry STRING INTO REGISTER $a0.
         li $v0, 4            #print_string>>>>>PRINTS OUT THE STRING retry TO THE USER TO PROMPT THE INPUT OF NEW NUMBERS.
         syscall              #used to call system services to perform I/O.
         j NUMBERS            #JUMPS BACK TO BACK TO THE TOP OF THE PROGRAM AFTER A SUCSSESSFUL COMPLRTION IN ORDER FOR THE
                              #USER TO TRY MORE NUMBERS.
        
