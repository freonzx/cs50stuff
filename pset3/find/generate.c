/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // Checks if enough arguments were supplied to the program, if not prints the usage
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // n receives to conversion of argv[1] to integer made by atoi function
    int n = atoi(argv[1]);

    // If the arg count is 3 gets the argv[2] which should be the seed value, calls atoi to get it's integer value
    // and uses it as seed, else, just use the system time as seed
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    //drand48 generates pseudo-random numbers using a linear congruential algorithm and 48-bit integer arithmetic.
    //So this line prints the pseudo-random numbers using our seed.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
