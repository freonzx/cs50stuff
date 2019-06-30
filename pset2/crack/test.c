#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <cs50.h>

static const char alphabet[] =
"abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static const int alphabetSize = sizeof(alphabet) - 1;

char bruteImpl(char* str, int index, int maxDepth)
{
	int i=0;
    for (i = 0; i < alphabetSize; ++i)
    {
        str[index] = alphabet[i];

        if (index == maxDepth - 1){
        	char *res;
		 	res = crypt(str,"50");
		 	return res;
		 //printf("%s\n", str);
	}
        else bruteImpl(str, index + 1, maxDepth);
    }
}

void bruteSequential(int maxLen)
{
    char* buf = malloc(maxLen + 1);
	int i=0;
    for (i = 1; i <= maxLen; ++i)
    {
        memset(buf, 0, maxLen + 1);
        bruteImpl(buf, 0, i);
    }

    free(buf);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: ./crack hash\n");
		return 1;
	}
	

	return 0;
}