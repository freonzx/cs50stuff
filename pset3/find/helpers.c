/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"
#include <stdio.h>

#define MAX 65536
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    //Binary Search
	if(n <= 0) return false;

    /*for (int i = 0; i < n; ++i)
    {
    	if (values[i] == value) return true;
    }*/
	int start=0,end=n,mid=0;

		while(start <= end){
		    mid= (start+end)/2;
    		if (value == values[mid])
    		{
    			return true;
    		}else if(value < values[mid]){
    			end = mid-1;
    		}else if(value > values[mid]){
    			start = mid+1;
    		}
		}
	
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
	/*Bubble sort
	int temp=0;
    for (int i = 0; i < n-1; ++i)
    {
    	for (int j = 0; j < (n-1-i); ++j)
    	{
    		if (values[j] > values[j+1])
    		{
    			temp = values[j];
    			values[j] = values[j+1];
    			values[j+1] = temp;
    		}
    	}
    }*/

    //Count Sort
    int count[MAX] = {0};
	int i=0,j=0;

	for (i = 0; i < n; ++i)
		count[values[i]]++;

    int d=0;
    for(i=0;i<=MAX;++i){
        for(j=1;j<=count[i];++j){
            values[d] = i;
            d++;
        }
    }

    return;
}
