/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include "HashTable.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    return CheckHashTable(word);
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *dictFile = fopen(dictionary, "r");
    if (dictFile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    char line[LONGEST_WORD];
    while (fscanf(dictFile, "%s", line) != EOF) {
        AddToHashTable(line);
    }
    fclose(dictFile);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return HashListSize;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for(int i=0; i < OXFORD_WORDS; i++)
    {
        ClearNode(stuff[i]);
    }
    HashListSize = 0;
    return true;
}
