#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
	//Checks if there's 2 arguments provided
	if (argc != 2)
	{
		printf("Usage: ./vigenere key\n");
		return 1;
	}
	//Pass the value of first argument to key for easier manipulation
	string key = argv[1];
	//Checks if there is non-alpha in key
	for(int i = 0, j = strlen(key); i < j; i++)
    {
        if (!isalpha(key[i]))
        {   
            printf("Usage: ./vigenere key\n");
            return 1;
        }
    }

	int keyLen = strlen(argv[1]);
	int keyCount = 0, offset= 0, cap= 0;

	printf("plaintext: ");
	string s = get_string();
	
	for (int i = 0, n = strlen(s); i < n; ++i)
	{
		if ( (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') )
		{
			//Calculates offset in case plain[index] is lowercase and key[index] is uppercase
			cap = (s[i] >= 'a' && s[i] <= 'z') ? 97 : 65;
			offset = (key[keyCount] >= 'a' && key[keyCount] <= 'z') ? key[keyCount]-97 : key[keyCount]-65;
			s[i] = (s[i]-cap)+offset;
			
			if (s[i] >= 26)
			{
				s[i] = (s[i]%26)+cap;
				keyCount++;
			}else{
				s[i] = s[i]+cap;
				keyCount++;
			}

		}
		if(keyCount >= keyLen) keyCount=0;
	}
	
	printf("ciphertext: %s\n",s);

	return 0;
}