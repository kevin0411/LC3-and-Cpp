/*
 * partner: kuanwei2
 * This program is used to create a Sparse Matrix using a list of tuple and perform addition of Matrices.
 * The first function is load_tuples, which takes a input file name and create a tuple head and a list of tuples that is sorted
 * and contains all the non-zero entries in the file and return the tuple head.
 * 
 * The second function is gv_tuples, which takes the tuple head and a specific row and col and return the value of the index in the 
 * matrix.
 * 
 * The third function is set_tuples, which takes the tuple head and a specific row and col and value and stored the value into the
 * tuple nodes that are at the row and col. If the value is 0, then we delete the node from the list, otherwise we modify the value in the node.
 * If the row and col is not in the list (zero entry), then we create a node and put the node in the list according to the order of row and col.
 * 
 * The fourth function is save_tuples, which takes the output file name and a tuple head and print out the list of tuples in the specified form.
 * 
 * The fifth function is add_tuples, which takes two tuple head one from matrix A and one from matrix B and return a tuple head of matrix C which 
 * is the addition result of matrix A and B.
 * 
 * The sixth function is destroy_tuples, which takes a tuple head and free all the tuple nodes in it.
 * 
 */
#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>




/*
 * Input: char* input_file
 * Return: sp_tuples *head
 * Description: takes a input file name and create a tuple head and a list of tuples that is sorted
 * and contains all the non-zero entries in the file and return the tuple head
 */
sp_tuples * load_tuples(char* input_file)
{
    FILE *input;                                                                    // create a file pointer
    input = fopen(input_file,"r");                                                  // open and read the input file into input
    sp_tuples *head = malloc(sizeof(sp_tuples*));                                   // initialize a sp_tuples pointer head and initialize its nz and tuples_head
    head->nz=0;                                                                    
    head->tuples_head = NULL;
    fscanf(input,"%d %d\n",&(head->m),&(head->n));                                  // stored the size of the matrix into head
    int row,col;                                                                    // initialize int row, col and double val for scanning the input file
    double val;
    while(fscanf(input,"%d %d %lf\n",&row,&col,&val)!=EOF){                         // keeps scanning input until the end of file
        set_tuples(head,row,col,val);                                               // use the function set_tuples to modify the list of tuples
    }
    fclose(input);                                                                  // close the file
    return head;                                                                    // return the sp_tuples head
}

/*
 * Input: sp_tuples * mat_t,int row,int col
 * Return: double head->value
 * Description: takes the tuple head and a specific row and col and return the value of the index in the 
 * matrix.
 */
double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    sp_tuples_node *head = mat_t->tuples_head;                                      // create a temporary sp_tuples_node to store the head of the list
    while(!(head->col==col && head->row==row)){                                     // keeps searching for the specified row and col in the list
        if(head->next!=NULL){
            head = head->next;                                                      // look for the next entry if the current one doesn't match
        }
        else{
            return 0;                                                               // if this is the end of the list, return 0(not found)
        }
    }
    return head->value;                                                             // if we find the node, return its value
}


/*
 * Input: sp_tuples * mat_t, int row, int col, double value
 * Return: NULL
 * Description: takes the tuple head and a specific row and col and value and stored the value into the
 * tuple nodes that are at the row and col. If the value is 0, then we delete the node from the list, otherwise we modify the value in the node.
 * If the row and col is not in the list (zero entry), then we create a node and put the node in the list according to the order of row and col.
 */
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    if(row >= mat_t->m || col >= mat_t->n){                                         // if it is out of bound, do nothing
        return;
    }
    sp_tuples_node *node = mat_t->tuples_head;                                      // create a sp_tuples_node to store the start of the list
    if(node==NULL && value!=0){                                                     // if the list is empty and value is non-zero 
        sp_tuples_node *new = malloc(sizeof(sp_tuples_node*));                      // create a node with the given rol, col, value
        new->row = row;
        new->col = col;
        new->value = value;
        new->next = NULL;                                                           // make it point to NULL as it is the end of the list
        mat_t->tuples_head = new;                                                   // make the head tuple points to it
        mat_t->nz++;                                                                // increment nz by 1
        return;                                                                     // return
    }
    sp_tuples_node *prev = mat_t->tuples_head;                                      // create a sp_tuples_node to store the previous node 
    prev = NULL;                                                                    // set it to NULL as first node doesn't have previous node
    do{
        if(node->row==row && node->col==col && value!=0){                           // if the current node is the node we are finding and value is non-zero
            node->value = value;                                                    // store the value into current node's value
            return;                                                                 // return
        }
        else if(node->row==row && node->col==col && value==0){                      // if the current node is the node we are finding and value is zero
            if(prev == NULL){                                                       // if this is the only non-zero entry
                mat_t->tuples_head=node->next;                                      // make the head point to NULL
                free(node);                                                         // destroy and free the current node
            }
            else{
                prev->next = node->next;                                            // make the previous node point to the next node
                free(node);                                                         // destroy and free the current node
            }
            mat_t->nz--;                                                            // decrease nz by 1
            return;                                                                 // return
        }
        else if((node->row*mat_t->n + node->col > row*mat_t->n+col) && value!=0){   // if the current node is greater than the node we are looking for and the value is non-zero
            sp_tuples_node *new = malloc(sizeof(sp_tuples_node*));                  // create a new node with given rol,col,value
            new->row = row;
            new->col = col;
            new->value = value;
            new->next = node;                                                       // make it point to the current node
            if(prev == NULL){                                                       // if the current node is the first node 
                mat_t->tuples_head = new;                                           // make the head points to the new node
            }
            else{
                prev->next = new;                                                   // otherwise, make previous node point to the new node
            }
            mat_t->nz++;                                                            // increment nz by 1
            return;                                                                 // return
        }
        prev = node;                                                                // set previous node to the current node
        node=node->next;                                                            // set current node to the next node
    } while(node!=NULL);                                                            // search until the end of the list
    if(value!=0){                                                                   // if the node is not found and the value is non-zero
        sp_tuples_node *new = malloc(sizeof(sp_tuples_node*));                      // create a new node with given row,col,value
        new->row = row;
        new->col = col;
        new->value = value;
        mat_t->nz++;                                                                // increase nz by 1
        new->next = NULL;                                                           // make new node point to NULL
        if(prev == NULL){                                                           // if the list is empty
                mat_t->tuples_head = new;                                           // add the node to the start of the list
        }
        else{
            prev->next = new;                                                       // add the node to the end of the list
        }
    }
    return;                                                                         // return
}


/*
 * Input: char * file_name, sp_tuples * mat_t
 * Return: NULL
 * Description: takes the output file name and a tuple head and print out the list of tuples in the specified form.
 */
void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE *output = fopen(file_name,"w");                                            // create a file pointer and open and write the file
    fprintf(output,"%d %d\n",mat_t->m,mat_t->n);                                    // write the size m and n of the given matrix
    if(mat_t->tuples_head!=NULL){                                                   // if the list is not empty
       sp_tuples_node *node = mat_t->tuples_head;
       for(int i=mat_t->nz;i>0;i--){                                                // iterate through each node and print their row, col, value
        fprintf(output,"%d %d %lf\n",node->row,node->col,node->value);        
        node = node->next;
       } 
    }
    fclose(output);                                                                 // close file
	return;                                                                         // return
}

/*
 * Input: sp_tuples * matA, sp_tuples * matB
 * Return: sp_tuples * matC
 * Description: takes two tuple head one from matrix A and one from matrix B and return a tuple head of matrix C which 
 * is the addition result of matrix A and B.
 */
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    sp_tuples * matC = malloc(sizeof(sp_tuples*));                                  // create a tuple head for storing matrix C
    matC->m = matA->m;                                                              // initialize its size as the same size as matrix A
    matC->n = matA->n;
    matC->nz = 0;                                                                   // initialize its nz to 0
    matC->tuples_head = NULL;                                                       // make it empty
    sp_tuples_node *node = matA->tuples_head;                                       // create a temporary node pointing to the first node of matrix A
    while(node!=NULL){
        set_tuples(matC,node->row,node->col,node->value);                           // iterate through each node in matrix A and put it in matrix C
        node = node->next;
    }
    node = matB->tuples_head;                                                       // create a temporary node pointing to the first node of matrix B
    while(node!=NULL){                                                              // iterate through each node in matrix B 
        double val = gv_tuples(matC,node->row,node->col);                           
        if(val==0){                                                                 // if matrix C has zero value at a certain row and col which matrix B is non-zero
            set_tuples(matC,node->row,node->col,node->value);                       // create a node in matrix C to store it
        }
        else{                                                                       // if matrix C is non zero at a a certain row and col which matrix B is non-zero
            set_tuples(matC,node->row,node->col,node->value+val);                   // add value in matrix B to it
        }
        node = node->next;                                                          
    }
	return matC;                                                                    // return matrix C
}   



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return matA;

}


/*
 * Input: sp_tuples * mat_t
 * Return: NULL
 * Description: takes a tuple head and free all the tuple nodes in it.
 */	
void destroy_tuples(sp_tuples * mat_t){
	sp_tuples_node *node= mat_t->tuples_head;                                       // create a node that points to the first node of the list
    free(mat_t);                                                                    // free the sp_tuple mat_t
    while(node!=NULL){                                                              // iterate through each node in the list
        sp_tuples_node *temp = node;                                                
        node = node->next;                                                          //look for the next node
        free(temp);                                                                 // free the current node
    }
    return;                                                                         // return
}  






