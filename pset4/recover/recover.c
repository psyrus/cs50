#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
  // ensure proper usage I add more
  if (argc < 2)
  {
    fprintf(stderr, "Usage: ./recover recovery-file\n");
    return 1;
  }
  char* infile = argv[1];

  FILE *searchFile = fopen(infile, "r");
  if(searchFile == NULL)
  {
    fprintf(stderr, "The file could not be opened at (%s)", infile);
    return 2;
  }

  //This is a comment

}