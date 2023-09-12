/*
 * partner: kuanwei2
 * This program is used to let user play the game 2048, where the user will determine the number of rows and columns of the game board.
 * 
 * The first function make_game will create a game structure with the rows and cols given by the user, initialize each cell to -1, and return the pointer to the game structure.
 * 
 * The second function remake_game will free the previous game structure and give it a new memory size with the new given sizes of the game and initialize
 * the game structure just like the first function.
 * 
 * The third function get_cell will determine whether the given row and col is in range and then return the pointer to the cell at the
 * given row and col in cur_game.
 * 
 * The fourth function move_w will move all the cells in cur_game upward and merge the cells with same value once in a move. Then, the score will be increased by the new merge value.
 * If all the cells keep the same after the move, the function will return 0. Otherwise, it will return 1.
 * 
 * The fifth function move_s will move all the cells in cur_game downward and merge the cells with same value once in a move. Then, the score will be increased by the new merge value.
 * If all the cells keep the same after the move, the function will return 0. Otherwise, it will return 1.
 * 
 * The sixth function move_a will move all the cells in cur_game leftward and merge the cells with same value once in a move. Then, the score will be increased by the new merge value.
 * If all the cells keep the same after the move, the function will return 0. Otherwise, it will return 1.
 * 
 * The seventh function move_d will move all the cells in cur_game rightward and merge the cells with same value once in a move. Then, the score will be increased by the new merge value.
 * If all the cells keep the same after the move, the function will return 0. Otherwise, it will return 1.
 * 
 * The last function illegal_move_check will create a copy of cur_game and see if any move can be made to the board.
 * If no move can be made, then the function will return 0. Otherwise, it will return 1.
 * 
 */
#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    for(int i=0;i<rows*cols;i++){                                         // iterate through each cell 
        mygame->cells[i]=-1;                                              // initialize each cell to -1
    }
    mygame->score = 0;                                                    // set the score in mygame to 0;
    mygame->rows = rows;                                                  // set the rows in mygame to given rows value;
    mygame->cols = cols;                                                  // set the cols in mygame to given cols value;
    return mygame;                                                        // return mygame
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
    for(int i=0;i<new_rows*new_cols;i++){                                 // iterate through each cell
        (*_cur_game_ptr)->cells[i]=-1;                                    // initialize each cell to -1
    }
    (*_cur_game_ptr)->score= 0;                                           // set the score in _cur_game_ptr to 0;
    (*_cur_game_ptr)->rows = new_rows;                                    // set the rows in _cur_game_ptr to given rows value;
    (*_cur_game_ptr)->cols = new_cols;                                    // set the cols in _cur_game_ptr to given cols value;
	return;	    
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    int col_num = cur_game->cols;                                       // initialize int variable col_num to store the cols value in cur_game
    int row_num = cur_game->rows;                                       // initialize int variable row_num to store the rows value in cur_game
    if(row<row_num && row>=0 && col<col_num && col>=0){                 // check if the row and col is in range
        int* pointer = cur_game->cells +row*col_num+col;                // if so, return the pointer that points to the cell
        return pointer;
    }
    return NULL;                                                        // else, return NULL
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
    int col_num = cur_game->cols;                                                           // initialize int variable col_num to store the cols value in cur_game
    int row_num = cur_game->rows;                                                           // initialize int variable row_num to store the rows value in cur_game
    int flag = 0;                                                                           // initialize int variable flag to check if the board is moved(1) or not(0)
    for(int j=0;j<col_num;j++){                                                             // iterate through each cell in cur_game except the last row as nothing will move to last row
        for(int i=0;i<row_num-1;i++){
            if(*(cur_game->cells+i*col_num+j)==-1){                                         // if the current cell is blank(-1)
                for(int k=i+1;k<row_num;k++){                                               // look for the cell below current row
                    if(cur_game->cells[k*col_num+j]!=-1){                                   // if there is a cell that is not blank
                        *(cur_game->cells+i*col_num+j) = *(cur_game->cells+k*col_num+j);    // swap it with the current cell
                        *(cur_game->cells+k*col_num+j) = -1;
                        flag=1;                                                             // set flag to 1 as we modify the board
                        break;                                                              // break in order to swap the cells only once
                    }
                }
            }
        }
    }
    for(int j=0;j<col_num;j++){                                                             // iterate through each cell in cur_game except the last row as nothing will move to last row
        for(int i=0;i<row_num-1;i++){
            if(*(cur_game->cells+i*col_num+j)!=-1 && 
            *(cur_game->cells+i*col_num+j) == *(cur_game->cells+(i+1)*col_num+j)){          // if current cell is not blank and has the same value as the one below it
                *(cur_game->cells+(i+1)*col_num+j) = -1;                                    // set the lower cell to -1(blank)
                *(cur_game->cells+i*col_num+j) *=2;                                         // multiply the current cell by 2 as the two cells' values combine
                cur_game->score += *(cur_game->cells +i*col_num+j);                         // increase the score by the value of new cell
                flag=1;                                                                     // set flag to 1 as we modify the board
            }
        }
    }                                                                                       // initialize int variable flag to check if the board is moved(1) or not(0)
    for(int j=0;j<col_num;j++){                                                             // iterate through each cell in cur_game except the last row as nothing will move to last row
        for(int i=0;i<row_num-1;i++){
            if(*(cur_game->cells+i*col_num+j)==-1){                                         // if the current cell is blank(-1)
                for(int k=i+1;k<row_num;k++){                                               // look for the cell below current row
                    if(cur_game->cells[k*col_num+j]!=-1){                                   // if there is a cell that is not blank
                        *(cur_game->cells+i*col_num+j) = *(cur_game->cells+k*col_num+j);    // swap it with the current cell
                        *(cur_game->cells+k*col_num+j) = -1;
                        flag=1;                                                             // set flag to 1 as we modify the board
                        break;                                                              // break in order to swap the cells only once
                    }
                }
            }
        }
    }
    if(flag){                                                                               // if the board is modified, return 1
        return 1;   
    }
    return 0;                                                                               // else return 0
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    int col_num = cur_game->cols;                                                           // initialize int variable col_num to store the cols value in cur_game
    int row_num = cur_game->rows;                                                           // initialize int variable row_num to store the rows value in cur_game
    int flag = 0;                                                                           // initialize int variable flag to check if the board is moved(1) or not(0)
    for(int j=0;j<col_num;j++){                                                             // iterate through each cell except the first row as nothing will move to first row
        for(int i=row_num-1;i>0;i--){                                                   
            if(cur_game->cells[i*col_num+j]==-1){                                           // if the current cell is blank(-1)
                for(int k=i-1;k>=0;k--){                                                    // look for the cell above current row
                    if(cur_game->cells[k*col_num+j]!=-1){                                   // if there is a cell that is not blank
                        cur_game->cells[i*col_num+j] = cur_game->cells[k*col_num+j];        // swap it with the current cell
                        cur_game->cells[k*col_num+j] = -1;
                        flag=1;                                                             // set flag to 1 as we modify the board
                        break;                                                              // break in order to swap the cells only once
                    }
                }
            }
        }
    }
    for(int j=0;j<col_num;j++){                                                             // iterate through each cell except the first row as nothing will move to first row
        for(int i=row_num-1;i>0;i--){
            if(cur_game->cells[i*col_num+j]!=-1 &&
             cur_game->cells[i*col_num+j] == cur_game->cells[(i-1)*col_num+j]){             // if current cell is not blank and has the same value as the one above it
                cur_game->cells[(i-1)*col_num+j] =-1;                                       // set the above cell to -1(blank)
                cur_game->cells[i*col_num+j] *=2;                                           // multiply the current cell by 2 as its value is the combination of the two cells
                cur_game->score += cur_game->cells[i*col_num+j];                            // increase the score by the value of new cell
                flag=1;                                                                     // set flag to 1 as we modify the board
            }
        }
    }
    for(int j=0;j<col_num;j++){                                                             // iterate through each cell except the first row as nothing will move to first row
        for(int i=row_num-1;i>0;i--){                                                   
            if(cur_game->cells[i*col_num+j]==-1){                                           // if the current cell is blank(-1)
                for(int k=i-1;k>=0;k--){                                                    // look for the cell above current row
                    if(cur_game->cells[k*col_num+j]!=-1){                                   // if there is a cell that is not blank
                        cur_game->cells[i*col_num+j] = cur_game->cells[k*col_num+j];        // swap it with the current cell
                        cur_game->cells[k*col_num+j] = -1;
                        flag=1;                                                             // set flag to 1 as we modify the board
                        break;                                                              // break in order to swap the cells only once
                    }
                }
            }
        }
    }
    if(flag){                                                                               // if the board is modified, return 1
        return 1;   
    }
    return 0;                                                                               // else return 0
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    int col_num = cur_game->cols;                                                           // initialize int variable col_num to store the cols value in cur_game
    int row_num = cur_game->rows;                                                           // initialize int variable row_num to store the rows value in cur_game
    int flag = 0;                                                                           // initialize int variable flag to check if the board is moved(1) or not(0)
    for(int i=0;i<row_num;i++){                                                             // iterate through each cell except the last col as nothing will move to last col
        for(int j=0;j<col_num-1;j++){
            if(cur_game->cells[i*col_num+j]==-1){                                           // if the current cell is blank(-1)
                for(int k=j+1;k<col_num;k++){                                               // look for the cell to the right of the current row
                    if(cur_game->cells[i*col_num+k]!=-1){                                   // if there is a cell that is not blank
                        cur_game->cells[i*col_num+j] = cur_game->cells[i*col_num+k];        // swap it with the current cell
                        cur_game->cells[i*col_num+k] = -1;
                        flag=1;                                                             // set flag to 1 as we modify the board
                        break;                                                              // break in order to swap the cells only once
                    }
                }
            }
        }
    }
    for(int i=0;i<row_num;i++){                                                             // iterate through each cell except the last col as nothing will move to last col
        for(int j=0;j<col_num-1;j++){
            if(cur_game->cells[i*col_num+j]!=-1 &&
             cur_game->cells[i*col_num+j] == cur_game->cells[i*col_num+j+1]){               // if current cell is not blank and has the same value as the one to the right of it
                cur_game->cells[i*col_num+j] *=2;                                           // multiply the current cell by 2 as its value is the combination of the two cells
                cur_game->cells[i*col_num+j+1] = -1;                                        // set the cell to the right of it to -1(blank)
                cur_game->score += cur_game->cells[i*col_num+j];                            // increase the score by the value of new cell
                flag=1;                                                                     // set flag to 1 as we modify the board
            }
        }
    }
    for(int i=0;i<row_num;i++){                                                             // iterate through each cell except the last col as nothing will move to last col
        for(int j=0;j<col_num-1;j++){
            if(cur_game->cells[i*col_num+j]==-1){                                           // if the current cell is blank(-1)
                for(int k=j+1;k<col_num;k++){                                               // look for the cell to the right of the current row
                    if(cur_game->cells[i*col_num+k]!=-1){                                   // if there is a cell that is not blank
                        cur_game->cells[i*col_num+j] = cur_game->cells[i*col_num+k];        // swap it with the current cell
                        cur_game->cells[i*col_num+k] = -1;
                        flag=1;                                                             // set flag to 1 as we modify the board
                        break;                                                              // break in order to swap the cells only once
                    }
                }
            }
        }
    }
    if(flag){                                                                               // if the board is modified, return 1
        return 1;   
    }
    return 0;                                                                               // else return 0
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int col_num = cur_game->cols;                                                           // initialize int variable col_num to store the cols value in cur_game
    int row_num = cur_game->rows;                                                           // initialize int variable row_num to store the rows value in cur_game
    int flag = 0;                                                                           // initialize int variable flag to check if the board is moved(1) or not(0)
    for(int i=0;i<row_num;i++){
        for(int j=col_num-1;j>0;j--){                                                       // iterate through each cell except the first col as nothing will move to first col
            if(cur_game->cells[i*col_num+j]==-1){                                           // if the current cell is blank(-1)
                for(int k=j-1;k>=0;k--){                                                    // look for the cell to the left of the current row
                    if(cur_game->cells[i*col_num+k]!=-1){                                   // if there is a cell that is not blank
                        cur_game->cells[i*col_num+j] = cur_game->cells[i*col_num+k];        // swap it with the current cell
                        cur_game->cells[i*col_num+k] = -1;
                        flag=1;                                                             // set flag to 1 as we modify the board
                        break;                                                              // break in order to swap the cells only once
                    }
                }
            }
        }
    }
    for(int j=col_num-1;j>0;j--){
        for(int i=0;i<row_num;i++){                                                         // iterate through each cell except the first col as nothing will move to first col
            if(cur_game->cells[i*col_num+j]!=-1 &&
             cur_game->cells[i*col_num+j] == cur_game->cells[i*col_num+j-1]){               // if current cell is not blank and has the same value as the one to the left of it
                cur_game->cells[i*col_num+j]*= 2;                                           // multiply the current cell by 2 as its value is the combination of the two cells
                cur_game->cells[i*col_num+j-1] =-1;                                         // set the cell to the right of it to -1(blank)
                cur_game->score += cur_game->cells[i*col_num+j];                            // increase the score by the value of new cell
                flag=1;                                                                     // set flag to 1 as we modify the board
            }
        }
    }
    for(int i=0;i<row_num;i++){
        for(int j=col_num-1;j>0;j--){                                                       // iterate through each cell except the first col as nothing will move to first col
            if(cur_game->cells[i*col_num+j]==-1){                                           // if the current cell is blank(-1)
                for(int k=j-1;k>=0;k--){                                                    // look for the cell to the left of the current row
                    if(cur_game->cells[i*col_num+k]!=-1){                                   // if there is a cell that is not blank
                        cur_game->cells[i*col_num+j] = cur_game->cells[i*col_num+k];        // swap it with the current cell
                        cur_game->cells[i*col_num+k] = -1;
                        flag=1;                                                             // set flag to 1 as we modify the board
                        break;                                                              // break in order to swap the cells only once
                    }
                }
            }
        }
    }
    if(flag){                                                                               // if the board is modified, return 1
        return 1;   
    }
    return 0;                                                                               // else return 0
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    int col_num = cur_game->cols;                                                           // initialize int variable col_num to store the cols value in cur_game
    int row_num = cur_game->rows;                                                           // initialize int variable row_num to store the rows value in cur_game
    game * copy = malloc(sizeof(game));                                                     // create a copy 
    copy->cells = malloc(row_num*col_num*sizeof(cell));                                     // give the cells in copy the same size as the one in cur_game
    for(int i=0;i<row_num*col_num;i++){                                                     // copy every cell value from cur_game to copy
        copy->cells[i]=cur_game->cells[i];
    }
    copy->score = 0;                                                                        // initialize the score in copy
    copy->rows = row_num;                                                                   // initialize the rows in copy to the rows in cur_game
    copy->cols = col_num;                                                                   // initialize the cols in copy to the cols in cur_game
    return (move_a(copy)||move_d(copy)||move_s(copy)||move_w(copy));                        // return whether there can be a valid move in copy or not
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
