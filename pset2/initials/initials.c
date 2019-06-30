#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = get_string();

    int p = 0;
    for (int i = 0,c= strlen(name); i < c; ++i)
    {
        if (name[i] != ' ' && p == 0)
        {
        	printf("%c",toupper(name[i]));
        	p=1;
        }
    	else if (name[i] == ' ' && name[i+1] != ' ') p=0;
    }
    puts("");
}