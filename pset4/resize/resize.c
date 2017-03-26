/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

// Use passing by memory address to edit the value directly
int GetAddedValue(double * value)
{
  int returnVal = (int)*value;
  *value = *value - (double)returnVal;
  return returnVal;
}

int main(int argc, char *argv[])
{
  // ensure proper usage
  if (argc < 4)
  {
    fprintf(stderr, "Usage: ./resize infile outfile size (float)\n");
    return 1;
  }

  // remember variables
  char *infile = argv[1];
  char *outfile = argv[2];
  double multiplier = atof(argv[3]);

  remove(outfile);
  // open input file
  FILE *inptr = fopen(infile, "r");
  if (inptr == NULL)
  {
    fprintf(stderr, "Could not open %s.\n", infile);
    return 2;
  }

  // open output file

  FILE *outptr = fopen(outfile, "w");
  if (outptr == NULL)
  {
    fclose(inptr);
    fprintf(stderr, "Could not create %s.\n", outfile);
    return 3;
  }

  // read infile's BITMAPFILEHEADER
  BITMAPFILEHEADER bf;
  fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

  // read infile's BITMAPINFOHEADER
  BITMAPINFOHEADER bi;
  fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

  // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
  if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
      bi.biBitCount != 24 || bi.biCompression != 0)
  {
    fclose(outptr);
    fclose(inptr);
    fprintf(stderr, "Unsupported file format.\n");
    return 4;
  }

  // determine padding for scanlines
  int oldPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
  int oldHeight = abs(bi.biHeight);
  int oldWidth = abs(bi.biWidth);
  // Update all relevant header variables to their new values
  /**********************************************************/
  printf("bfSize: %d\n", bf.bfSize);
  printf("biWidth: %d\n", bi.biWidth);
  printf("biHeight: %d\n", bi.biHeight);
  printf("biSizeImage: %d\n", bi.biSizeImage);

  bi.biWidth = (int)(bi.biWidth * multiplier);
  bi.biHeight = (int)(bi.biHeight * multiplier);
  bi.biSizeImage = abs(bi.biWidth * bi.biHeight) * sizeof(RGBTRIPLE);
  bf.bfSize = sizeof(bf) + sizeof(bi) + bi.biSizeImage;

  //Check updated values
  printf("----------\n");
  printf("bfSize: %d\n", bf.bfSize);
  printf("biWidth: %d\n", bi.biWidth);
  printf("biHeight: %d\n", bi.biHeight);
  printf("biSizeImage: %d\n", bi.biSizeImage);

  /**********************************************************/

  // write outfile's BITMAPFILEHEADER
  fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

  // write outfile's BITMAPINFOHEADER
  fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

  // determine padding for scanlines
  int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

  //multiplier = 5.7
  double nFactor, remainder;

  remainder = modf(multiplier, &nFactor);
  //remainder = 0.7, nFactor = 5.0
  double verticalSubFactor = 0.0;
  double horizontalSubFactor = 0.0;

  int incrementor = (int)nFactor;
  int verticalCounter = 0;
  int countlines =0;
  int amountRead = 0;

  int pixelDuplicateExtraTimes = 0;
  int rowDuplicateExtraTimes = 0;

  RGBTRIPLE *row;
  row = malloc(bi.biWidth * sizeof(RGBTRIPLE));
  printf("Using all: %d %d %f %f %d %d %d\n", oldPadding, newPadding, verticalSubFactor, horizontalSubFactor, countlines, amountRead, oldWidth);
  printf("Incrementor: %d, remainder: %f padding: %d bfSize: %d\n", incrementor, remainder, newPadding, bf.bfSize);

  for(int i = 0; i < oldHeight && verticalCounter < abs(bi.biHeight); i++)
  {
    verticalSubFactor += remainder;
    rowDuplicateExtraTimes = GetAddedValue(&verticalSubFactor);
    printf("Writing a row\n");
    int newPxCounter = 0;
    //Get the heap data from the line
    for(int j=0; j < oldWidth; j++)
    {
      horizontalSubFactor += remainder;
      pixelDuplicateExtraTimes = GetAddedValue(&horizontalSubFactor);
      RGBTRIPLE thisPixel;
      fread(&thisPixel, sizeof(RGBTRIPLE), 1, inptr);
      for(int k = 0; k < incrementor + pixelDuplicateExtraTimes; k++)
      {
        row[newPxCounter] = thisPixel;
        newPxCounter++;
      }
      printf("Writing a column %d times ", incrementor);
    }
    // skip over padding, if any
    fseek(inptr, oldPadding, SEEK_CUR);
    printf("\n");

    //Write the heap data as many times as it needs to be done for the row
    for(int r = 0; r < incrementor + rowDuplicateExtraTimes; r++)
    {
      fwrite(row, bi.biWidth * sizeof(RGBTRIPLE), 1, outptr);
      // then add it back (to demonstrate how)
      for (int p = 0; p < newPadding; p++)
      {
        fputc(0x00, outptr);
      }
    }
  }

  free(row);

  printf("sizeof RGBTRIPLE: %li\n", sizeof(RGBTRIPLE));
  printf("sizeof row: %li\n", sizeof(row));

  // close infile
  fclose(inptr);

  // close outfile
  fclose(outptr);

  // success
  return 0;
  }