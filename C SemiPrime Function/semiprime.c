/* partner: kuanwei2
 * This program is used to check if a number is a semiprime or prime
 * The first error is in is_prime function where the program return 1
 * when the number is divisible by another number or in other words, not prime number.
 * Therefore, the error will cause the function to return 0 when the number is prime instead.
 * So,the function should return 0 instead when the number is not prime.
 * The second error is in print_semiprimes function where k is set to i%j. Instead,
 * it should be set to i/j as k is used to store the number whose product with j is i. 
 * Thus, this error will always set k to 0 as the program will only enter here when i is
 * divisible by j, which will always cause the function to identify i as not semiprime.
 * The third error is that the function didn't set ret to 1 when the function finds a
 * semiprime. This error will cause ret always be 0. Thus, we should add a line after print("%d",i)
 * to set ret to 1 because at this moment, we are sure that i is a semiprime.
 * The last error is that the function will print a semiprime more than once if it is the product of
 * more than one combination of two prime numbers. This will cause the function to print the same semiprime
 * more than once in some situations. Thus, we should add a break after we found a number is a semiprime,
 * so the function will look at the next number instead of next combination.
 */

#include <stdlib.h>
#include <stdio.h>


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
			ret = 1;
			break;
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
