/*
 * partner: kuanwei2
 * This program is used to help the user to find a solution for the maze.
 * The first function is called createMaze which takes a character pointer fileName
 * and create a maze_t structure with given height, width, and cells stored in it and return it.
 * The second function is destroyMaze, which takes the maze_t pointer and free all its memory.
 * The third function is printMaze, which takes the maze_t pointer and print all its cells.
 * The fourth function is solveMazeDFS, which takes the maze_t pointer and current column
 * and row and return 1 if the maze is solvable and 0 otherwise.
 */

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    FILE * maze_file = fopen(fileName,"r");                                 // open the file with reading mode
    maze_t * maze = malloc(sizeof(*maze));                                  // create a maze_t pointer and malloc with size of maze
    fscanf(maze_file,"%d %d\n",&maze->width,&maze->height);                 // store the width and height in the file into maze
    maze->cells = malloc(sizeof(*(maze->cells))*(maze->height));            // malloc the memory of maze cells with size of height
    for(int i=0;i<maze->height;i++){                                        
        maze->cells[i]= malloc(sizeof(*(maze->cells[0]))*maze->width);      // in each cells, malloc the memory with size of width
    }
    for(int i=0;i<maze->height;i++){    
        for(int j=0;j<maze->width;j++){
            maze->cells[i][j] = (char)fgetc(maze_file);                     // iterate through each cells and store the character from file in it
            if(maze->cells[i][j]=='S'){                                     // if it is a start, store the current col and row into start col and row
                maze->startColumn=j;
                maze->startRow=i;
            }
            if(maze->cells[i][j]=='E'){                                     // if it is an end, store the current col and row into end col and row
                maze->endColumn=j;
                maze->endRow=i;
            }
        }
        fgetc(maze_file);                                                   // read the new line(\n)
    }
    fclose(maze_file);                                                      // close the file
    return maze;                                                            // return the maze
    
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    for(int i=0;i<maze->height;i++){
        free(maze->cells[i]);                                               // free the memory in each cell
    }
    free(maze->cells);                                                      // free the cells
    free(maze);                                                             // free the maze


}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    for(int i=0;i<maze->height;i++){
        for(int j=0;j<maze->width;j++){                                     // iterate through each row and column
            printf("%c",maze->cells[i][j]);                                 // print the character stored in the cell
        }
        printf("\n");                                                       // print a new line
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    if(col<0 || col>=maze->width || row<0 || row>=maze->height){            // if current rol or col is out of bound, return 0
        return 0;
    }
    if(maze->cells[row][col]=='E'){                                         // if it reaches the end, return 1(solvable)
        return 1;
    }
    if(maze->cells[row][col]!=' ' && maze->cells[row][col]!='S'){           // if it is not a path and not a start, return 0
        return 0;
    }
    if(maze->cells[row][col]!='S'){                                         // mark the path if it is not a start
        maze->cells[row][col]='*';
    }
    if(solveMazeDFS(maze,col-1,row))return 1;                               // return 1 if going left is solvable
    if(solveMazeDFS(maze,col,row+1))return 1;                               // return 1 if going down is solvable
    if(solveMazeDFS(maze,col+1,row))return 1;                               // return 1 if going right is solvable
    if(solveMazeDFS(maze,col,row-1))return 1;                               // return 1 if going up is solvable

    if(maze->cells[row][col]!='S'){                                         // if it is not a start, mark it as walked pass(but not part of solution)
        maze->cells[row][col]='~';
    }
    return 0;                                                               // return 0 if it is not solvable
}
