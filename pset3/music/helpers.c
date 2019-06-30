// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int x = atoi(&fraction[0]);
    int y = atoi(&fraction[2]);
    if (y == 8)
    {
        return x;
    }
    else if (y == 4)
    {
        return x * 2;
    }
    else if (y == 2)
    {
        return x * 4;
    }
    return 0;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    float n = 0;
    float octal = 0;

    if (strlen(note) == 3)
    {
	    char accid = note[1];
	    octal = atoi(&note[2]);
		if (accid == '#')
		{
			n += 1;
		}
		else if (accid == 'b')
		{
			n -= 1;
		}
	}
	else
	{
		octal = atoi(&note[1]);
	}

    char letter = note[0];

    switch
    (letter)
    {
        case 'A':
            n += 0;
            break;
        case 'B':
            n += 2;
            break;
        case 'G':
            n -= 2;
            break;
        case 'F':
            n -= 4;
            break;
        case 'E':
            n -= 5;
            break;
        case 'D':
            n -= 7;
            break;
        case 'C':
            n -= 9;
            break;
    }
    n += (octal - 4) * 12;
    float power = n / 12;
    float f = round(pow(2, power) * 440);
    return f;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
