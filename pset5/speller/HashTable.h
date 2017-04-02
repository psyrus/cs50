#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdbool.h>
#include "string.h"
#define MULTIPLIER (37)
#define OXFORD_WORDS (200000)

typedef struct HASHNODE HASHNODE;

struct HASHNODE
{
    char* storedString;
    HASHNODE* next;
};

HASHNODE* hashTable[OXFORD_WORDS];
long HashListSize;

/**
 * The function to create the array position for a given key string
 */
unsigned long hash(const char* s);

/**
 * Adds a string as a key to the hash table
 */
void AddToHashTable(char* string);

/**
 * Function to find the last node on a linked list (recursively)
 */
HASHNODE* GetLastNode(HASHNODE* currentNode);

/**
 * Check if some value exists in the hash table
 */
bool CheckHashTable(const char* string);

/**
 * Function to clear the memory of the hash nodes
 */
void ClearNode(HASHNODE* node);

#endif
