/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{

  //Constant setup, always decrement from d*d-1 down to 1
  int currentValue = d*d - 1;
  bool oddTiles = (d % 2 == 0);
  // Vertical loop
  for(int i = 0; i < d; i++)
  {
    //horizontal loop
    for(int j = 0; j < d; j++)
    {
      board[i][j] = currentValue;
      currentValue--;
    }
  }

  //Special case for only odd number of tiles, make second last two 1, 2
  if(oddTiles)
  {
    board[d-1][d-3] = 1;
    board[d-1][d-2] = 2;
  }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
  for(int i = 0; i < d; i++)
  {
    //horizontal loop
    for(int j = 0; j < d; j++)
    {
      if(board[i][j] == 0)
      {
        printf("□\t");
        continue;
      }
      printf("%d\t", board[i][j]);
    }
    printf("\n\n");
  }

}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // Search for position of tile.
    int posX = -1;
    int posY = -1;

    int zeroPosX = -1;
    int zeroPosY = -1;
    //Vertical loop
    for(int i = 0; i < d; i++)
    {
      //horizontal loop
      for(int j = 0; j < d; j++)
      {
        if(board[i][j] == tile)
        {
          posX = j;
          posY = i;
        }
        else if(board[i][j] == 0)
        {
          zeroPosX = j;
          zeroPosY = i;
        }
      }
    }

    printf("Tile (%d): %d, %d\n", tile, posX, posY);
    printf("Zero: %d, %d\n", zeroPosX, zeroPosY);
    //Then check if the found position has a 0 i+1 or i -1, j+1 or j-1
    int diffY = abs(zeroPosY - posY);
    int diffX = abs(zeroPosX - posX);
    if(diffX * diffY != 0 || diffY > 1 || diffX > 1)
    {
      return false;
    }

    //switch y position of zero and tile
    board[zeroPosY][zeroPosX] = tile;
    board[posY][posX] = 0;
    return true;
}


/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
  //inefficient way
    bool allCorrect = true;
    int checkValue = 1;
    //Vertical loop
    for(int i = 0; i < d && allCorrect; i++)
    {
      //horizontal loop
      for(int j = 0; j < d && allCorrect; j++)
      {
        if(i == d-1 && j == d-1)
        {
          checkValue = 0;
        }
        //printf("Checking if position [%d][%d] is '%d', it is: %d\n", i, j, checkValue, board[i][j]);
        allCorrect = board[i][j] == checkValue;
        checkValue++;
      }
    }
    //printf("allCorrect is: %s\n\n", allCorrect ? "true" : "false");
    return allCorrect;

  // Efficient way
    // Keep track of how many items are in the right spot, updating just the current two.
    // If the number of correct items is equal to the number of tiles, count as a win.
}
