#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

typedef uint8_t BYTE;

bool isJpegStart(BYTE * readBlock)
{
  int legitBytes[] = {0xff,0xd8,0xff};
  int legitBytesLength = sizeof(legitBytes)/sizeof(legitBytes[0]);

  //Check first 3 standard bytes
  for(int i=0; i < legitBytesLength; i++)
  {
    if(readBlock[i] != legitBytes[i])
    {
      return false;
    }
  }

  int legitBits[] = {0,1,1,1};
  int legitBitsLength = sizeof(legitBits)/sizeof(legitBits[0]);
  //Check 4th byte such that it's first four bits are 1110
  for(int i=0; i<legitBitsLength; i++)
  {
    if(readBlock[3] >> i & (1-legitBits[i]))
    {
      return false;
    }
  }
  return true;
}

int main(int argc, char *argv[])
{
  // ensure proper usage
  if (argc < 2)
  {
    fprintf(stderr, "Usage: ./recover recovery-file\n");
    return 1;
  }
  char* infile = argv[1];

  FILE *outputFile = NULL;
  FILE *searchFile = fopen(infile, "r");

  if(searchFile == NULL)
  {
    fprintf(stderr, "The file could not be opened at (%s)", infile);
    return 2;
  }


  //Block size is 512 Bytes
  int blockSize = 512;
  int readSize = blockSize * sizeof(BYTE);
  char* filePrefix = "recovered-jpg-";
  char* fileExtension = ".jpg";
  int recoveredFiles = 0;

  BYTE* block = malloc(readSize);

  while(fread(block, sizeof(BYTE), blockSize, searchFile) == blockSize)
  {
    if(isJpegStart(block))
    {
      recoveredFiles++;

      if(outputFile != NULL)
        fclose(outputFile);

      int length = snprintf(NULL, 0,"%d",recoveredFiles);
      char fileName[strlen(filePrefix) + length + strlen(fileExtension) + 1];
      snprintf(fileName, sizeof(fileName), "%s%d%s", filePrefix, recoveredFiles, fileExtension);

      outputFile = fopen(fileName, "w");
    }

    if(outputFile != NULL)
    {
      fwrite(block, blockSize, 1, outputFile);
    }
  }

  printf("Found %d files\n", recoveredFiles);
  if(searchFile != NULL)
    fclose(searchFile);

  if(outputFile != NULL)
    fclose(outputFile);

  free(block);
  return 0;



}