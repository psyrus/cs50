/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"
// maximum amount of hay
const int MAXSIZE = 65536;
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
  if(n < 1)
  {
      return false;
  }
  printf("Length: %d\n", n);
  int upper = n - 1;
  int lower = 0;
  int testIndex;
  int steps = 0;
  while(upper > lower)
  {
    steps++;
    testIndex = lower + (int)((upper - lower) / 2);
    printf("[%d] TestIndex changed to: %d\n",steps, testIndex);
    if(value == values[testIndex])
    {
        printf("Took %d steps", steps);
        return true;
    }
    else if(value > values[testIndex])
    {
        lower = testIndex + 1;
    }
    else 
    {
        upper = testIndex - 1;
    }
  }
  printf("Took %d steps", steps);
  return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int totalIterations = 0;
    int allNums[MAXSIZE];
    for(int i=0; i < MAXSIZE; i++)
    {
      allNums[i] = 0;
      totalIterations++;
    }
    
    for(int i = 0; i < n; i++)
    {
      allNums[values[i]]++;
      totalIterations++;
    }
    
    int outputIndex = 0;
    for(int i = 0; i < MAXSIZE; i++)
    {
      while(allNums[i] > 0)
      {
        values[outputIndex] = i;
        allNums[i]--;
        totalIterations++;
        outputIndex++;
      }
      totalIterations++;
    }
    
    printf("Sorting took %d iterations\n**************\n[", totalIterations);
    for(int i = 0; i < n; i++)
    {
      printf("%d ", values[i]);
    }
    printf("]\n**************\n");
    return;
}
