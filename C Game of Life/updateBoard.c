/*
 * partner: kuanwei2
 * This program includes all the functions needed for the game of life.
 * The first function countLiveNeighbor helps to count the number of 
 * alive cell, which is 1, around the current cell indicated by row and col.
 * The second function updateBoard is used to update all the status of cell
 * to the status of next generation. The rule is that if an alive cell has two or three
 * alive cells around it, it will be alive for the next generation. Also, if
 * a dead cell is surrounded by exact three alive cells, it will be alive for next generation.
 * Otherwise, the remaining cells will be dead. The third function is to determine whether
 * the alive cells are stable, which will return 1 if next generation is the same as the current
 * and return 0 otherwise.
 */

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
	int count=0;									// initialize counter
	for(int i=row-1;i<=row+1;i++){							// look for all rows around the current value
		if(i>=0 && i<boardRowSize){						// make sure current row is not out of bound
			for(int j=col-1;j<=col+1;j++){					// look for all columns around the current value
				if(j>=0 && j<boardColSize){				// make sure current column is not out of bound
					if(!(i==row && j==col)){			// make sure not to count the current value
						if(board[boardColSize*i+j]==1)count++;  // if it is alive, counter plus one 
					}
				}
			}
		}
	}
	return count;									// return counter
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
	int temp[boardRowSize*boardColSize];							// initialize an array for storing value for next gen
	for(int i=0;i<boardRowSize;i++){							// look for all the cells
		for(int j=0;j<boardColSize;j++){
			int num = countLiveNeighbor(board,boardRowSize,boardColSize,i,j); 	// create an integer variable to store the number of cells around the current cell
			if(board[boardColSize*i+j]==1 && (num==2 || num==3)){ 			// if it is alive and has 2 or 3 alive cells around it, its next generation will be alive
				temp[boardColSize*i+j]=1;
			}
			else if(board[boardColSize*i+j]==0 && num==3){ 				// if it is dead and has 3 alive cells around it, its next generation will be alive
				temp[boardColSize*i+j]=1;
			}
			else{									// otherwise, the next generation will be dead
				temp[boardColSize*i+j]=0;
			}
		}	
	}
	for(int i=0;i<boardRowSize;i++){
		for(int j=0;j<boardColSize;j++){
			board[boardColSize*i+j] = temp[boardColSize*i+j]; 			// copy the next generation cells to the current board
		}
	}
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
	int new[boardRowSize*boardColSize];					// initialize an array for storing new generation cells
	for(int i=0;i<boardRowSize;i++){
		for(int j=0;j<boardColSize;j++){
			new[i*boardColSize+j]=board[i*boardColSize+j];		// copy the board to new array
		}
	}
	updateBoard(new,boardRowSize,boardColSize);				// update the new array
	for(int i=0;i<boardRowSize;i++){
		for(int j=0;j<boardColSize;j++){
			if(new[i*boardColSize+j]!=board[i*boardColSize+j]){	// if new generation is different from current board, return 0
				return 0;
			}
		}
	}
	return 1;								// otherwise, return 1
}

				
				
			

