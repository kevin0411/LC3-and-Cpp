;partners: kuanwei2, sychang5
;Date: 9/15/2022
;this program is used to calculate the postfix expressions the user enter to the keyboard
;using stack, and the result will be stored in R5. If there is a underflow, or unrecognized input
;(input that is not operand or operator), or the stack contains more than 1 result, the message
;"Invalid Expression" will then be printed. Otherwise, when "=" is typed, the program will
;print the calculated answer in hexadecimals.
;
	.ORIG x3000	
;Register Table
;R0 = Input value and output value
;R1 = Group counter for PRINT_HEX
;R2 = Store value of 4 bits number in PRINT_HEX
;R3 = Store 1st operand
;R4 = Store 2nd operand
;R5 = Store the result
;R6 = Store temp value
;R7 = Store PC address for RET

;your code goes here
	AND R0,R0,#0	;Clear R0
	AND R1,R1,#0	;Clear R1
	AND R2,R2,#0	;Clear R2
	AND R3,R3,#0	;Clear R3
	AND R4,R4,#0	;Clear R4
	AND R5,R5,#0	;Clear R5
	AND R6,R6,#0	;Clear R6
	AND R7,R7,#0	;Clear R7
	ST R7,PRINT_STAT ;Store 0 to PRINT_STAT
	TOP		
	GETC		; Get user input
	OUT		; Echo back to screen
	JSR EVALUATE	; Call Subroutine EVALUATE to identify operands and operators
	LD R6,PRINT_STAT ;Load R6 with PRINT_STAT
	BRz TOP		; Go back to TOP to get another input
	BRp PRINTOUT	;Go to PRINTOUT
	LEA R0,INVALID_MESSAGE	;Load R0 with starting address of INVALID_MESSAGE
	PUTS			;Print the string starts with the address in R0
	BRnzp DONE		;Go to DONE
	PRINTOUT
	JSR PRINT_HEX		;Call subroutine PRINT_HEX
	DONE
	HALT			; Stop the program


INVALID_MESSAGE .STRINGZ "Invalid Expression" 	; String "Invalid Expression"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
	ST R7,STORE_R7_SOMEWHERE
	JSR POP		;Pop the result 
	ADD R5,R0,#0	;Store the result to R5
	ADD R3,R0,#0    ;Store value to print to R3
	AND R1,R1,#0	;Clear R1
	ADD R1,R1,#4    ;Count number of group of 4 bits
NEXT_HEX
	AND R2,R2,#0	;Clear R2
	AND R4,R4,#0	;Clear R4
	ADD R4,R4,#4    ;Count number of bits in current group
CALC_HEX
	ADD R2,R2,R2	;Left shift R2
	AND R3,R3,R3	;Check R3
	BRzp ZERO_MSB	;If R3 has MSB 0, go to ZERO_MSB
	ADD R2,R2,#1	;If R3 has MSB 1, add 1 to R2
ZERO_MSB
	ADD R3,R3,R3    ;Left shift R3
	ADD R4,R4,#-1	;Subtract bit counter R4 by 1
	BRp CALC_HEX	;If R4>0, go to CALC_HEX
	ADD R2,R2,#-9	;Otherwise, subtract R2 by 9
	BRp BIGGER_THAN_TEN	;If R2>0, go to BIGGER_THAN_TEN
	ADD R2,R2,#9	;Restore R2
	LD R0, ZERO_VAL	;Load ASCII value of '0' to R0
	ADD R0,R2,R0	;ADD R2 to R0
	OUT			;Print R0
	BRnzp CONDITION	;Go back to CONDITION
BIGGER_THAN_TEN
	ADD R2,R2,#9	;Restore R2
	ADD R2,R2,#-10	;Subtract R2 by 10
	LD R0, A_VAL	;Load R0 with ASCII value of 'A'
	ADD R0,R2,R0	;ADD R2 to R0
	OUT		;Print R0
CONDITION
	ADD R1,R1,#-1	;Subtract the group counter R1 by 1
	BRp NEXT_HEX	;If it is positive, go to NEXT_HEX
	LD R7,STORE_R7_SOMEWHERE	;LOAD R7 with STORE_R7_SOMEWHERE
	RET		;Return

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;
;
EVALUATE
	LD R6,MULT_NEGATIVE_VAL	;Load R6 with negative of ASCII value of '*'
	ADD R0,R0,R6		;Add to the input value R0
	BRz JUMP_MUL		;If it is 0, go to JUMP_MUL
	LD R6,MULT_VAL		;Load R6 with ASCII value of '*'
	ADD R0,R0,R6		;Restore R0
	LD R6,DIV_NEGATIVE_VAL	;Load R6 with negative of ASCII value of '/'
	ADD R0,R0,R6		;Add to the input value R0
	BRz JUMP_DIV		;If it is 0, go to JUMP_DIV
	LD R6,DIV_VAL		;Load R6 with ASCII value of '/'
	ADD R0,R0,R6		;Restore R0
	LD R6,POW_NEGATIVE_VAL	;Load R6 with negative of ASCII value of '^'
	ADD R0,R0,R6		;Add to the input value R0
	BRz JUMP_EXP		;If it is 0, go to JUMP_EXP
	LD R6,POW_VAL		;Load R6 with ASCII value of '^'
	ADD R0,R0,R6		;Restore R0
	LD R6,PLUS_NEGATIVE_VAL	;Load R6 with negative of ASCII value of '+'
	ADD R0,R0,R6		;Add to the input value R0
	BRz JUMP_PLUS		;If it is 0, go to JUMP_PLUS
	LD R6,PLUS_VAL		;Load R6 with ASCII value of '+'
	ADD R0,R0,R6		;Restore R0
	LD R6,MINUS_NEGATIVE_VAL ;Load R6 with negative of ASCII value of '-'
	ADD R0,R0,R6		;Add to the input value R0
	BRz JUMP_MIN		;If it is 0, go to JUMP_MIN
	LD R6,MINUS_VAL		;Load R6 with ASCII value of '-'
	ADD R0,R0,R6		;Restore R0
	LD R6,EQUAL_NEGATIVE_VAL ;Load R6 with negative of ASCII value of '='
	ADD R0,R0,R6		;Add to the input value R0
	BRz ANS			;If it is 0, go to ANS
	LD R6,EQUAL_VAL		;Load R6 with ASCII value of '='
	ADD R0,R0,R6		;Restore R0
	LD R6,SPACE_NEGATIVE_VAL ;Load R6 with negative of ASCII value of '[space]'
	ADD R0,R0,R6		;Add to the input value R0
	BRnp FIND_NUM		;If it is 0, go to FIND_NUM
	RET			;Return
	FIND_NUM
	LD R6,SPACE_VAL		;Load R6 with ASCII value of '[space]'
	ADD R0,R0,R6		;Restore R0
	LD R6,ZERO_NEGATIVE_VAL	;Load R6 with negative of ASCII value of '0'
	ADD R0,R0,R6		;Add to the input value R0
	BRn NOT_NUM		;If it is negative, go to NOT_NUM
	ADD R0,R0,#-9		;Subtract R0 by 9
	BRnz NUM		;If it is not positive, go to NUM
	NOT_NUM		
	BRnzp INVALID		;Go to INVALID
	NUM
	ADD R0,R0,#9		;Restore R0
	ST R7,STORE_R7_SOMEWHERE ;Store R7 at STORE_R7_SOMEWHERE
	JSR PUSH		;Call Subroutine PUSH
	LD R7,STORE_R7_SOMEWHERE ;Restore R7 back
	RET			;Return
	JUMP_MUL
	ST R7,STORE_R7_SOMEWHERE ;Store R7 at STORE_R7_SOMEWHERE
	JSR POP			;Call subroutine POP
	AND R5,R5,R5		;Check R5
	BRnz NORMAL		;If it is not 1, it is not underflow
	AND R5,R5,#0
	ADD R5,R5,#-1		;Set R5 to -1
	ST R5,PRINT_STAT	;Store -1 to PRINT_STAT
	RET			;Return
	NORMAL
	ADD R3,R0,#0		;Store the pop value R0 in R3
	JSR POP			;Call subroutine POP
	AND R5,R5,R5		;Check R5
	BRnz NORMAL1		;If it is not 1, it is not underflow
	AND R5,R5,#0
	ADD R5,R5,#-1		;Set R5 to -1
	ST R5,PRINT_STAT	;Store -1 to PRINT_STAT
	RET			;Return
	NORMAL1
	ADD R4,R0,#0		;Store the pop value R0 in R4
	JSR MUL			;Call subroutine MUL
	JSR PUSH		;Call subroutine PUSH
	LD R7,STORE_R7_SOMEWHERE ;Restore R7 back
	RET			;Return
	JUMP_DIV
	ST R7,STORE_R7_SOMEWHERE ;Store R7 at STORE_R7_SOMEWHERE
	JSR POP			;Call subroutine POP
	AND R5,R5,R5		;Check R5
	BRnz NORMAL2		;If it is not 1, it is not underflow
	AND R5,R5,#0
	ADD R5,R5,#-1		;Set R5 to -1
	ST R5,PRINT_STAT	;Store -1 to PRINT_STAT
	RET			;Return
	NORMAL2
	ADD R4,R0,#0		;Store the pop value R0 in R4
	JSR POP			;Call subroutine POP
	AND R5,R5,R5		;Check R5
	BRnz NORMAL3		;If it is not 1, it is not underflow
	AND R5,R5,#0
	ADD R5,R5,#-1		;Set R5 to -1
	ST R5,PRINT_STAT	;Store -1 to PRINT_STAT
	RET			;Return
	NORMAL3
	ADD R3,R0,#0		;Store the pop value R0 in R3
	JSR DIV			;Call subroutine DIV
	JSR PUSH		;Call subroutine PUSH
	LD R7,STORE_R7_SOMEWHERE ;Restore R7 back
	RET			;Return
	JUMP_EXP
	ST R7,STORE_R7_EXP ;Store R7 at STORE_R7_EXP
	JSR POP			;Call subroutine POP
	AND R5,R5,R5		;Check R5
	BRnz NORMAL4		;If it is not 1, it is not underflow
	AND R5,R5,#0
	ADD R5,R5,#-1		;Set R5 to -1
	ST R5,PRINT_STAT	;Store -1 to PRINT_STAT
	RET			;Return
	NORMAL4
	ADD R4,R0,#0		;Store the pop value R0 in R4
	JSR POP			;Call subroutine POP
	AND R5,R5,R5		;Check R5
	BRnz NORMAL5		;If it is not 1, it is not underflow
	AND R5,R5,#0
	ADD R5,R5,#-1		;Set R5 to -1
	ST R5,PRINT_STAT	;Store -1 to PRINT_STAT
	RET			;Return
	NORMAL5
	ADD R3,R0,#0		;Store the pop value R0 in R3
	JSR EXP			;Call subroutine EXP
	JSR PUSH		;Call subroutine PUSH
	LD R7,STORE_R7_EXP ;Restore R7 back
	RET			;Return
	JUMP_PLUS
	ST R7,STORE_R7_SOMEWHERE ;Store R7 at STORE_R7_SOMEWHERE
	JSR POP			;Call subroutine POP
	AND R5,R5,R5		;Check R5
	BRnz NORMAL6		;If it is not 1, it is not underflow
	AND R5,R5,#0
	ADD R5,R5,#-1		;Set R5 to -1
	ST R5,PRINT_STAT	;Store -1 to PRINT_STAT
	RET			;Return
	NORMAL6
	ADD R4,R0,#0		;Store the pop value R0 in R4
	JSR POP			;Call subroutine POP
	AND R5,R5,R5		;Check R5
	BRnz NORMAL7		;If it is not 1, it is not underflow
	AND R5,R5,#0
	ADD R5,R5,#-1		;Set R5 to -1
	ST R5,PRINT_STAT	;Store -1 to PRINT_STAT
	RET			;Return
	NORMAL7
	ADD R3,R0,#0		;Store the pop value R0 in R3
	JSR PLUS		;Call subroutine PLUS
	JSR PUSH		;Call subroutine PUSH
	LD R7,STORE_R7_SOMEWHERE ;Restore R7 back
	RET			;Return
	JUMP_MIN
	ST R7,STORE_R7_SOMEWHERE ;Store R7 at STORE_R7_SOMEWHERE
	JSR POP			;Call subroutine POP
	AND R5,R5,R5		;Check R5
	BRnz NORMAL8		;If it is not 1, it is not underflow
	AND R5,R5,#0
	ADD R5,R5,#-1		;Set R5 to -1
	ST R5,PRINT_STAT	;Store -1 to PRINT_STAT
	RET			;Return
	NORMAL8
	ADD R4,R0,#0		;Store the pop value R0 in R4
	JSR POP			;Call subroutine POP
	AND R5,R5,R5		;Check R5
	BRnz NORMAL9		;If it is not 1, it is not underflow
	AND R5,R5,#0
	ADD R5,R5,#-1		;Set R5 to -1
	ST R5,PRINT_STAT	;Store -1 to PRINT_STAT
	RET			;Return
	NORMAL9
	ADD R3,R0,#0		;Store the pop value R0 in R3
	JSR MIN			;Call subroutine MIN
	JSR PUSH		;Call subroutine PUSH
	LD R7,STORE_R7_SOMEWHERE ;Restore R7 back
	RET			;Return
	ANS
	LD R3,STACK_START	;Load STACK_START to R3
	LD R4,STACK_TOP		;Load STACK_TOP to R4
	NOT R4,R4		;Turn R4 to -R4
	ADD R4,R4,#1
	ADD R3,R3,R4		;ADD R4 to R3
	ADD R3,R3,#-1		;Check if R3 equals 0
	BRnp INVALID		;If it is not zero, go to INVALID
	AND R3,R3,#0	
	ADD R3,R3,#1		;Set R3 to 1
	ST R3,PRINT_STAT	;Store 1 in PRINT_STAT
	RET			;Return
	INVALID
	AND R3,R3,#0
	ADD R3,R3,#-1		;Set R3 to -1
	ST R3,PRINT_STAT	;Store -1 in PRINT_STAT
	RET			;Return


PRINT_STAT    .FILL x0000			; Print status
STORE_R7_EXP	.BLKW #1





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS    
;your code goes here
ADD R0,R4,R3	;ADD two inputs into R0
RET		;Return
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN
;your code goes here
NOT R4,R4	;Set R4 to -R4
ADD R4,R4,#1
ADD R0,R4,R3	;ADD R4 to R3
RET		;Return
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL
;your code goes here
AND R6,R6,#0
ST R6,NEG
ST R4,TEMP	;Store R4 at TEMP
AND R3,R3,R3	;Check R3
BRz ZERO	;If it is 0, go to ZERO
BRp POS_R3	;Go to POS_R3
LD R6,NEG
ADD R6,R6,#1
ST R6,NEG	;Store NEG+1 to NEG
NOT R3,R3
ADD R3,R3,#1 	;Turn R3 to positive
POS_R3
AND R4,R4,R4	;Check R4
BRz ZERO	;If it is 0, go to ZERO
BRp POS_R4
LD R6,NEG
ADD R6,R6,#1
ST R6,NEG	;Store NEG+1 to NEG
NOT R4,R4
ADD R4,R4,#1 	;Turn R3 to positive
POS_R4
AND R0,R0,#0	;Clear R0
LOOP
ADD R0,R0,R3	;Add R3 to R0
ADD R4,R4,#-1	;Subtract R4 by 1
BRp LOOP	;If R4 is positive, go to LOOP
LD R4,TEMP	;Restore R4
LD R6,NEG
ADD R6,R6,#-1
BRz TURN_NEG
RET		;Return
ZERO
AND R0,R0,#0	;Clear R0
RET		;Return
TURN_NEG
NOT R0,R0
ADD R0,R0,#1	;Turn R0 to -R0
RET

NEG  .BLKW #1			; Record if there's negative num
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
ST R7,STORE_R7_SOMEWHERE	;Store R7 at STORE_R7_SOMEWHERE
AND R1,R1,#0			;Clear R1
ADD R1,R1,R4			;ADD R4 to R1
ADD R4,R3,#0			;ADD R3 to R4
KEEP_MUL
ADD R1,R1,#-1			;Decrease R1 by 1
BRz BACK			;If it is zero, go to BACK
JSR MUL				;Call subroutine MUL
ADD R3,R0,#0			;Set R0 to R3
BRnzp KEEP_MUL			;Go to KEEP_MUL
BACK
LD R7,STORE_R7_SOMEWHERE	;Restore R7
ADD R0,R3,#0			;Set R3 to R0
RET				;Return


STORE_R7_SOMEWHERE  .BLKW #1			; Place to store R7 temporarily
   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV
;your code goes here
NOT R4,R4	;Set R4 to -R4
ADD R4,R4,#1
AND R0,R0,#0	;Clear R0
CONT
ADD R3,R3,R4	;Add R4 to R3
BRn PUSHH	;If it is negative, go to PUSHH
ADD R0,R0,#1	;Increase R0 by 1
BRnzp CONT	;Go to CONT
PUSHH
RET		;Return
   

A_VAL       .FILL x0041     			; ASCII value of 'A'
ZERO_VAL    .FILL x0030     			; ASCII value of '0'
TEMP    .BLKW #1				; Place to store temp value
EQUAL_VAL   .FILL x003D				; ASCII value of '='
EQUAL_NEGATIVE_VAL  .FILL xFFC3			; negative ASCII value of '='
SPACE_VAL   .FILL x0020				; ASCII value of '[space]'
SPACE_NEGATIVE_VAL  .FILL xFFE0			; negative ASCII value of '[space]'
MULT_VAL    .FILL x002A				; ASCII value of '*'
MULT_NEGATIVE_VAL   .FILL xFFD6			; negative ASCII value of '*'
DIV_VAL     .FILL x002F				; ASCII value of '/'
DIV_NEGATIVE_VAL    .FILL xFFD1			; negative ASCII value of '/'
POW_VAL     .FILL x005E				; ASCII value of '^'
POW_NEGATIVE_VAL    .FILL xFFA2			; negative ASCII value of '^'
PLUS_VAL    .FILL x002B				; ASCII value of '+'
PLUS_NEGATIVE_VAL   .FILL xFFD5			; negative ASCII value of '+'
MINUS_VAL   .FILL x002D				; ASCII value of '-'
MINUS_NEGATIVE_VAL  .FILL xFFD3			; negative ASCII value of '-'
ZERO_NEGATIVE_VAL   .FILL xFFD0			; negative ASCII value of '0'

   
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;

;


PUSH    
    ST R3, PUSH_SaveR3  ;save R3
    ST R4, PUSH_SaveR4  ;save R4
    AND R5, R5, #0      ;
    LD R3, STACK_END    ;
    LD R4, STACK_TOP    ;
    ADD R3, R3, #-1     ;
    NOT R3, R3      ;
    ADD R3, R3, #1      ;
    ADD R3, R3, R4      ;
    BRz OVERFLOW        ;stack is full
    STR R0, R4, #0      ;no overflow, store value in the stack
    ADD R4, R4, #-1     ;move top of the stack
    ST R4, STACK_TOP    ;store top of stack pointer
    BRnzp DONE_PUSH     ;
OVERFLOW
    ADD R5, R5, #1      ;
DONE_PUSH
    LD R3, PUSH_SaveR3  ;
    LD R4, PUSH_SaveR4  ;
    RET


PUSH_SaveR3 .BLKW #1    ;
PUSH_SaveR4 .BLKW #1    ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
    ST R3, POP_SaveR3   ;save R3
    ST R4, POP_SaveR4   ;save R3
    AND R5, R5, #0      ;clear R5
    LD R3, STACK_START  ;
    LD R4, STACK_TOP    ;
    NOT R3, R3      ;
    ADD R3, R3, #1      ;
    ADD R3, R3, R4      ;
    BRz UNDERFLOW       ;
    ADD R4, R4, #1      ;
    LDR R0, R4, #0      ;
    ST R4, STACK_TOP    ;
    BRnzp DONE_POP      ;
UNDERFLOW
    ADD R5, R5, #1      ;
DONE_POP
    LD R3, POP_SaveR3   ;
    LD R4, POP_SaveR4   ;
    RET


POP_SaveR3  .BLKW #1    ;
POP_SaveR4  .BLKW #1    ;
STACK_END   .FILL x3FF0 ;
STACK_START .FILL x4000 ;
STACK_TOP   .FILL x4000 ;

.END

