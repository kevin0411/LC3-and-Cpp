; partner: kuanwei2, sychang5
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing

ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop

; partner: kuanwei2, sychang5
; you will need to insert your code to print the histogram here
; Introduction
; the remaining part of the program is going to print out each character
; and its value in histogram in hexadecimal form in a new line
; and in the form "char 0000"
; for example, if there's 18 A in the histogram
; then, the program will print "A 0012" as 0012 is hexadecimal for 18


; table of register use in this part of the code
;    R0 holds a temporary ASCII value for printing out
;    R1 holds the bit counter to make it count how many bits
;       we have calculated in this group of 4 bits
;    R2 holds the pointer to address of current character in histogram
;    R3 holds the ASCII value of current character in histogram
;    R4 holds the group counter to make it count
;       how many groups of 4 bits we have calculated
;    R5 holds the sum of the four bits we are looking at
;    R6 holds the value of current character in histogram


PRINT_HIST
	AND R0,R0,#0		; clear R0
	AND R1,R1,#0		; clear R1
	AND R2,R2,#0		; clear R2
	AND R3,R3,#0		; clear R3
	AND R4,R4,#0		; clear R4
	AND R5,R5,#0		; clear R5
	AND R6,R6,#0		; clear R6
	LD R3,AT		; set R3 to ASCII value of '@'
	LD R2,HIST_ADDR		; copy start of histogram into R2
PRINT_LOOP
	AND R0,R0,#0		; clear R0
	ADD R0,R0,R3		; add the ASCII value of current char to R0
	OUT			; print out the current char
	LD R0, SPACE		; load R0 with ASCII value of 'space'
	OUT			; print out space
	LDR R6,R2,#0		; load R6 with the value of current char in the histogram
	LD R4, BIT_COUNT	; load R4 with bit counter, which is 4, to make it count
				; how many groups of 4 bits we have calculated
NEXT_HEX
	AND R5,R5,#0		; clear R5
	LD R1, BIT_COUNT	; load R1 with bit counter, which is 4, to make it count how many bits
				; we have calculated in this group of 4 bits
CALC_HEX
	ADD R5,R5,R5		; left shift R5
	AND R6,R6,R6		; set cc to check R6
	BRzp ZERO_MSB		; if it is non-negative, goes to ZERO_MSB
	ADD R5,R5,#1		; add a value of 1 to R5
ZERO_MSB
	ADD R6,R6,R6		; left shift R6
	ADD R1,R1,#-1		; decrease the bit counter by 1
	BRp CALC_HEX		; if the bit counter is not set to zero, meaning that we didn't finish calculating
				; the value of a group of four bits, then goes to CALC_HEX
	ADD R5,R5,#-9		; check if R5 is greater than 9
	BRp BIGGER_THAN_NINE	; go to BIGGER_THAN_NINE if true
	ADD R5,R5,#9		; set R5 to its original value
	LD R0, ZERO_VAL		; load R0 with ASCII value of '0'
	ADD R5,R5,R0		; add R5 with R0 to get the ASCII value of current values in R5
	AND R0,R0,#0		; clear R0
	ADD R0,R0,R5		; add R0 with R5
	OUT			; print out the value of R5 (group of 4 bits)
	BRnzp CONDITION		; go to CONDITION
BIGGER_THAN_NINE
	ADD R5,R5,#9		; add R5 with 9 to restore its original value
	ADD R5,R5,#-10		; subtract R5 from 10 
	LD R0, A_VAL		; load R0 with the ASCII value of 'A'
	ADD R0,R0,R5		; add R0 to R5 to make it to hexadecimal(A-F)
	OUT			; print out the value of R5 (group of 4 bits) 
CONDITION
	ADD R4,R4,#-1		; decrease R4 the group counter by 1
	BRp NEXT_HEX		; if the bit counter is positive, go to NEXT_HEX
	ADD R2,R2,#1		; increase R2 (the address of current character) by 1
	ADD R3,R3,#1		; increase R3 (the current character) by 1
	LD R0, NEG_Z		; load R0 with inverse of ASCII 'Z'
	ADD R0,R0,R3		; add R0 with R3
	BRp DONE		; if the R0 is positive, meaning next char exceeds 'Z', then go to DONE
	LD R0, NEW_LINE		; load R0 with ASCII value of 'New Line'
	OUT			; print out new line
	BRnzp PRINT_LOOP	; go back to PRINT_LOOP
	

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments



DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT		.FILL x0040	; ASCII value of '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
NEW_LINE	.FILL x000A 	; ASCII value of 'NEW LINE'
SPACE		.FILL x0020 	; ASCII value of 'SPACE'
A_VAL		.FILL x0041 	; ASCII value of 'A'
ZERO_VAL	.FILL x0030 	; ASCII value of '0'
BIT_COUNT	.FILL #4 	; store value 4
NEG_Z		.FILL xFFA6	; inverse of ASCII 'Z'


; for testing, you can use the lines below to include the string in this
; program...
;STR_START	.FILL STRING	; string starting address
;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

.END
