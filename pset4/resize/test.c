#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void testMem(int * Value)
{
  *Value = 5;
}

int main(int argc, char *argv[])
{
  if(argc){}
  int width = 5;
  int height = 7;
  double multiplier = atof(argv[1]);

  int horizontalPixels = (int)(width * multiplier);
  int verticalPixels = (int)(height * multiplier);

  printf("With multiplier of [%f]:\nOld\tNew\n----\t----\nx: %d\t%d\ny: %d\t%d\n", multiplier, width, horizontalPixels, height, verticalPixels);
  //return 1;

  double nFactor, remainder;

  remainder = modf(multiplier, &nFactor);

  double verticalSubFactor = 0.0;
  double horizontalSubFactor = 0.0;

  int incrementor = (int)nFactor;
  int verticalCounter = 0;
  int countlines =0;
  printf("Incrementor: %d, remainder: %f\n", incrementor, remainder);
  for(int i = 0; i < height && verticalCounter < verticalPixels; i=i*1)
  {
    // Increment the decimal portion and the rows count
    verticalSubFactor += remainder;
    verticalCounter++;

    // We move on to the next row of the "original" image's pixels only when we have looped enough times (by the multiplier)
    if(verticalCounter % incrementor == 0)
    {
      i++;
    }

    // If the decimal component has reached or exceeded 1, we should add an extra row (of the current one) so it is consistent with the original multiplier
    if(verticalSubFactor - 1.0 > -0.001)
    {
      i--;
      verticalSubFactor -= 1.0;
    }

    // The horizontal component's decimal factor will be reset each row
    horizontalSubFactor = 0.0;
    for(int j = 0; j < width; j++)
    {
      // Just like for the vertical rows, accumulate the decimal component separately
      horizontalSubFactor += remainder;

      // These are the original pixels (printed out as many times as the integer multiplier component dictates: 5.7 -> 5 times)
      for(int k = 0; k < incrementor; k++)
      {
        printf(".");
      }
      //If the decimal component has reached or exceeded 1,
      while(horizontalSubFactor - 1.0 > -0.001)
      {
        printf("x");
        horizontalSubFactor -= 1.0;
      }
    }

    countlines++;
    //printf(" %d lines @ i=%d (%d | %d)", countlines, i, verticalCounter, (int)verticalSubFactor);
    printf("\n");
  }

  printf("\n\n------ Testing Memory Pass ------- \n\n");
  int val = 1;
  printf("Initial Value: %d\n", val);
  testMem(&val);
  printf("Final Value: %d\n", val);
}