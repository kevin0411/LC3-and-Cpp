/*
partner:kuanwei2
The program is used to print the specific row of the pascal triangle
requested by the user. The program will first print "Enter a row index:"
and ask the user to input the number, which starts from 0. Then, it will 
print the pascal number of that specific row.
*/
 
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int row; 							//declare an integer variable row for storing the input
	printf("Enter a row index: ");					//print "Enter a row index:"
	scanf("%d",&row);						//store the input into variable row
	unsigned long product = 1;					//declare an unsigned long variable product and set it to 1
	for(int i=0;i<row+1;i++){					//the for loop starts from i=0 to i=row
		if(i==0){						//if i = 0
			printf("1 ");					//print "1"
		}
		else{							//else
			double temp = (double)product*(row+1-i)/i;	//declare a double variable temp to store the product of the current (row+1-i)/i to the previous product according to the equation for pascal's triangle
			product = (unsigned long)temp;			//store the temp into product
			printf("%ld ",product);				//print the product out with a space after
		}
	}
	printf("\n");							//print a newline after all numbers are printed
  return 0;
}
