#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{

  if(argc != 3)
  {
    fprintf(stderr, "Usage: ./whodunit infile outfile\n");
    return 1;
  }

  // remember filenames
  char *infile = argv[1];
  char *outfile = argv[2];

  //Attempt to open file
  FILE *inputFile;
  inputFile=fopen(infile, "r");
  if(inputFile == NULL)
  {
    fprintf(stderr, "Could not open the file at [%s], please check the path.\n", infile);
    return 2;
  }

  //Attempt to open the file for writing
  FILE *outputFile;
  outputFile = fopen(outfile, "w");
  if(outfile == NULL)
  {
    fprintf(stderr, "Could not open the file [%s] for writing, please check the permissions or if it is open by another user.\n", outfile);
    return 3;
  }

  // read inputFile's BITMAPFILEHEADER
  BITMAPFILEHEADER bf;
  fread(&bf, sizeof(BITMAPFILEHEADER), 1, inputFile);

  // read inputFile's BITMAPINFOHEADER
  BITMAPINFOHEADER bi;
  fread(&bi, sizeof(BITMAPINFOHEADER), 1, inputFile);



  //Check that the file is a 24bit uncompressed bmp 4.0 (?)
  if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
  {
    fclose(outputFile);
    fclose(inputFile);
    fprintf(stderr, "Unsupported file format.\n");
    return 4;
  }

  // write outfile's BITMAPFILEHEADER
  fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outputFile);

  // write outfile's BITMAPINFOHEADER
  fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outputFile);

  //Remove the red component from every BGR pixel and output the file
    //Start looping from the bytes of the image data (bfOffBits as the offset from the start of the file. )
    // On each iteration, change the R component to 000000
    // Write to file?

  // determine padding for scanlines
  int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

  // iterate over infile's scanlines
  for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
  {
      // iterate over pixels in scanline
      for (int j = 0; j < bi.biWidth; j++)
      {
          // temporary storage
          RGBTRIPLE triple;

          // read RGB triple from infile
          fread(&triple, sizeof(RGBTRIPLE), 1, inputFile);
          if(triple.rgbtRed == 0xff)
          {
            triple.rgbtBlue = 0xff;
            triple.rgbtGreen = 0xff;
          }
          else
          {
            triple.rgbtRed = 0x00;
            triple.rgbtBlue = 0x00;
            triple.rgbtGreen = 0x00;
          }

          // write RGB triple to outfile
          fwrite(&triple, sizeof(RGBTRIPLE), 1, outputFile);
      }

      // skip over padding, if any
      fseek(inputFile, padding, SEEK_CUR);

      // then add it back (to demonstrate how)
      for (int k = 0; k < padding; k++)
      {
          fputc(0x00, outputFile);
      }
  }
  //Save the file
  // close infile
  fclose(inputFile);

  // close outfile
  fclose(outputFile);

  return 0;

}