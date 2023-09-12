/*
 * partner: kuanwei2
 * This program is used to solve the sudoku puzzle with the user
 * gives an input sudoku, which is in size of 9x9 and consists of number from 0 to 9.
 * Cells filled with 0 are unfilled. The program will help to solve the puzzle
 * which can make every row and column and 3x3 boxes all only consist of one of each number
 * from 1 to 9. This program consists of several functions. 
 * 
 * The first function is is_val_in_row, which takes the parameter val, i, sudoku 
 * and will return 1 if the value val appears in row i in sudoku array and return 0 otherwise.
 * 
 * The second function is is_val_in_col, which takes the parameter val, j, sudoku 
 * and will return 1 if the value val appears in col j in sudoku array and return 0 otherwise.
 * 
 * The third function is is_val_in_3x3_zone, which takes the parameter val,i,j, sudoku 
 * and will return 1 if the value val appears in the 3x3 zone around row i and col j in sudoku array and return 0 otherwise.
 * 
 * The fourth function is is_val_valid, which takes the parameter val, i,j, sudoku 
 * and will return 1 if the value val can be placed at sudoku[i][j]
 * 
 * The fifth function is all_filled, which takes the parameter sudoku 
 * and will return 1 if all values in sudoku array is non-zero and return 0 otherwise.
 * 
 * The sixth function is solve_sudoku, which takes the parameter sudoku 
 * and will return 1 if the sudoku is completed. Otherwise, it will guess number from 0 to 9
 * at all unfilled places and find a solution. If there's no solution, then it will return 0.
 * 
 */

#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  // BEG TODO
  for(int j=0;j<9;j++){       // iterate through each value in the current row i
    if(sudoku[i][j]==val){    // return 1 if val appears in the row i
      return 1;
    }
  }
  return 0;                   // otherwise, return 0
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);
  // BEG TODO  
  for(int i=0;i<9;i++){       // iterate through each value in the current col j
    if(sudoku[i][j]==val){    // return 1 if val appears in the col j
      return 1;
    }
  }
  return 0;                   // otherwise, return 0
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9 && j>=0 && j<9);
  // BEG TODO
  for(int r=i/3*3;r<i/3*3+3;r++){     // iterate through the rows in current 3x3 zone
    for(int c=j/3*3;c<j/3*3+3;c++){   // iterate through the cols in current 3x3 zone
      if(sudoku[r][c]==val){          // return 1 if val appears in 3x3 zone
        return 1;
      }
    }
  }
  return 0;                           // otherwise, return 0
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_3x3_zone(val,i,j,sudoku)==0 && is_val_in_col(val,j,sudoku)==0 && is_val_in_row(val,i,sudoku)==0){
    return 1;       // if val is not in current row, col, and 3x3 zone, return 1
  }
  return 0;         // otherwise, return 0
  // END TODO
}

// Function: all_filled
// Return true if all values in sudoku is non-zero (filled)
int all_filled(const int sudoku[9][9]){
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){   // iterate through every value in sudoku array
      if(sudoku[i][j]==0){  // if the cell is unfilled (0), return 0
        return 0;
      }
    }
  }
  return 1;                 // otherwise, return 1
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i,j;
  if(all_filled(sudoku)){               // return 1 if sudoku array is fully filled(completed)
    return 1;
  }
  else{
    for(int row=0;row<9;row++){         // otherwise, iterate through each row of sudoku
      int flag = 0;                     // initialize a flag to record whether a non_filled cell is found or not
      for(int col=0;col<9;col++){       // iterate through each column of sudoku
        if(sudoku[row][col]==0){       
          i=row;                        // record the row and column of the unfilled cell into i and j
          j=col;
          flag=1;                       // set flag to 1
          break;                        // break and stop finding
        }
      }
      if(flag){
        break;                          // if flag ==1 (unfilled cell found), break
      }
    }
  }
  for(int num=1;num<=9;num++){          // try every number from 1 to 9
    if(is_val_valid(num,i,j,sudoku)){   // if the number can be placed in current cell
      sudoku[i][j]=num;                 // temperorily place it into the cell for guess
      if(solve_sudoku(sudoku)){
        return 1;                       // return 1 if it works
      }
      sudoku[i][j]=0;                   // otherwise, set it back to 0(unfilled)
    }
  }
  return 0;                             // return 0 if every guess failed
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





