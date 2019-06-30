#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("How many minutes?\n");
    int min = get_int();
    printf("%d bottles.\n",min*12);
}