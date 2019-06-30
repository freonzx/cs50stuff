#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <crypt.h>

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		printf("Usage: ./crack hash\n");
		return 1;
	}
	
	string pass = crypt(argv[1],"50");

	printf("%s\n",pass);

	return 0;
}