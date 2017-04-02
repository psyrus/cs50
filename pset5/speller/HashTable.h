#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdbool.h>
#include "string.h"
#define MULTIPLIER (37)
#define OXFORD_WORDS (200000)
#define LONGEST_WORD (45)

typedef struct HASHNODE HASHNODE;

struct HASHNODE
{
    char* storedString;
    HASHNODE* next;
};

HASHNODE* stuff[OXFORD_WORDS];
long HashListSize;

void AddToHashTable(char* string);

HASHNODE* GetLastNode(HASHNODE* currentNode);

bool CheckHashTable(const char* string);

unsigned long hash(const char* s);

void ClearNode(HASHNODE* node);

#endif
