#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		printf("Needs 2 arguments\n");
		return 1;
	}

	int key = atoi(argv[1]);

	printf("plaintext: ");
	string s = get_string();
	
	for (int i = 0, n = strlen(s); i < n; ++i)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
		{
			s[i] = (s[i]-97)+key;
			if (s[i] >= 26)
			{
				s[i] = (s[i]%26)+97;
			}else{
				s[i] = s[i]+97;
			}

		}else if (s[i] >= 'A' && s[i] <= 'Z')
		{
			s[i] = (s[i]-65)+key;
			if (s[i] >= 26)
			{
				s[i] = (s[i]%26)+65;
			}else{
				s[i] = s[i]+65;
			}
		}
	}
	
	printf("ciphertext: %s\n",s);

	return 0;
}