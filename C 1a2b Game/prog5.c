/* 
 * partner: kuanwei2			
 * The program is used to play a game which the user has to first set a seed for
 * srand function. Then, the program will generate a random 4 numbers solution
 * each number is from 1 to 8. The user will have 12 guesses to guess. After each guess
 * the program will tell the user the amount of perfect matches and misplaced matches
 * in the guess. Perfect match is when the user guess is in exact same place and same number
 * with the solution. Misplaced match is literally when user guess has same number but in different
 * place. In addition, if the seed and guess the user inputs are not in the correct format,
 * the program will print a warning and ask user to input again.
 * 
 */


/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 

//    seed and post are declared for sscanf to store these values in variables
      int seed;
      char post[2];
//    The sscanf statement below reads the integer into seed. 
      int num_read = sscanf (seed_str, "%d%1s", &seed, post);
//    The srand(seed) helps to set seed for the game
      srand(seed);

//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below

//    if the user only types an integer, return 1
      if(num_read == 1)return 1;
//    if not, then print the warning and return 0
      printf("set_seed: invalid seed\n");
      return 0;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here

/*
 *  as rand()%8 gives number from 0 to 7, we set each solution to rand()%8+1 so they are from 1 to 8
 *  which is what the rule is for the game. Then, each solution is stored into static vairable called solution
 */
    *one = rand()%8 +1;
    solution1 = *one;
    *two = rand()%8 +1;
    solution2 = *two;
    *three = rand()%8 +1;
    solution3 = *three;
    *four = rand()%8 +1;
    solution4 = *four;
//  guess_number is set to 1
    guess_number =1;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,

//  first declared w,x,y,z,post[2] for sscanf to store
    int w,x,y,z;
    char post[2];
//  read the input from the user and store the amount of variables read into variable num_read
    int num_read = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
//  initialize integer variable perfect and misplaced as counter of perfect and misplaced matches
    int perfect = 0, misplaced = 0;
//  determine if there are 4 integers read and each of them is from 1 to 8
    if(num_read == 4 && w>=1 && w<=8 && x>=1 && x<=8 && y>=1 && y<=8 && z>=1 && z<=8){
	// set each guess value to the intended output
	*one = w;
	*two = x;
	*three = y;
	*four = z;
	// declare an integer array and store each guess value in it
	int guess[4];
	guess[0] = w;
	guess[1] = x;
	guess[2] = y;
	guess[3] = z;
	// declare an integer array and store each solution value in it
	int temp[4];
	temp[0] = solution1;
	temp[1] = solution2;
	temp[2] = solution3;
	temp[3] = solution4;
	// use for loop to see if any pair of guess and solution that is in same place is matched(perfect match)
	for(int i=0;i<4;i++){
	  if(guess[i] == temp[i]){
		// increase the counter for perfect match if there is a perfect match
		perfect++;
		// set both guess and solution to 0 to mark them as matched(used)
		guess[i]=0;
		temp[i]=0;
	  }	
	}
	for(int i=0;i<4;i++){
	  // if the solution we are looking at is already matched, skip it
	  if(temp[i]==0){
		continue;
	  }
	  else{
		// otherwise, we look through each guess to see misplaced match
	  	for(int j=0;j<4;j++){
		  if(temp[i]==guess[j]){
			// if there is misplaced match, increase the counter and set the guess to 0 to mark it as matched
			misplaced++;
			guess[i]=0;
			// then we skip the rest of the guess and look for the next solution
			break;
		  }
		}
	  }
	}
	// print the result after looking through all the perfect and misplaced matches
	printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n",guess_number, perfect, misplaced);
	// return 1 when the guess is valid
	return 1;
    }
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed

    //print the warning and return 0 when the guess is invalid
    printf("make_guess: invalid guess\n");
    return 0;
}


