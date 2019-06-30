#include <stdio.h>
#include <cs50.h>

int check_card(long long number);

int main()
{
    int con=0;
    long long num=0;
    
    printf("Number:\n");
    num = get_long_long();
    

    long long temp = num;

    while(temp) //Counts digits
	{
	    con++;
	    temp /= 10;
	}

	//printf("%d digits\n",con);

	temp = num;

	while (temp > 100LL) //Gets 2 First digits
    {
        temp = temp / 10LL;
    }

    int company_id = temp;

    //printf("Comp ID %d \n",company_id);

    if (check_card(num) == 1 && con > 13)
    {
    	if (company_id > 50 && company_id < 56 && con == 16)
	    {
	        printf("MASTERCARD\n") ;
	    }
	    else if ((company_id == 34 || company_id == 37) && (con == 15)) 
	    {
	        printf("AMEX\n") ;
	    }
	    else if ((company_id / 10 == 4) && (con == 13 || con == 16 || con == 19))
	    {
	        printf("VISA\n") ;
	    }

    }else{
    	printf("INVALID\n");
    }

    return 0;
}

int check_card(long long number){
	int sum = 0, count=0;

	while(number) //Counts digits
	{
	    count++;
	    number /= 10;
	}

    for (int i = 1; i <= count; i++)
    {
        int digit = number % 10LL;

        if (i % 2 == 0)
        {
            digit *= 2;

            if (digit > 9)
            {
                digit -= 9;
            }
        }

        sum += digit;

        number /= 10LL;
    }

    if (sum % 10 == 0) return 1;
    else return 0;

}