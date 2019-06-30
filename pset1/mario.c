#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int num;
    do{
        printf("Height:\n");
        num = get_int();
    }while(num > 23 || num < 0);
    
    for (int i = 1; i <= num; ++i)
    {
    	for (int k = 0; k < num-i ; ++k)
    	{
    		printf(" ");
    	}
    	for (int j = 0; j < i; ++j)
    	{
    		printf("#");
    	}
    	printf("  ");
    	for (int j = 0; j < i; ++j)
    	{
    		printf("#");
    	}
    	printf("\n");
    }
}