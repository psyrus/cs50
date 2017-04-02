#include "HashTable.h"
#include <stdio.h>

unsigned long hash(const char *s)
{

    unsigned long h;
    unsigned const char *us;

    /* cast s to unsigned const char * */
    /* this ensures that elements of s will be treated as having values >= 0 */
    us = (unsigned const char *) s;

    h = 0;
    while(*us != '\0') {
        h = h * MULTIPLIER + *us;
        us++;
    }

    return h % OXFORD_WORDS;
}

void AddToHashTable(char* string)
{
    unsigned long arrayPos = hash(string);
    HASHNODE* nodePtr = malloc(sizeof(HASHNODE));
    nodePtr->next = NULL;
    nodePtr->storedString = malloc(strlen(string)+1);
    strcpy(nodePtr->storedString, string);
    if(stuff[arrayPos] == NULL)
    {
        stuff[arrayPos] = nodePtr;
    }
    else
    {
        HASHNODE* lastNode = GetLastNode(stuff[arrayPos]);
        lastNode->next = nodePtr;
    }
    HashListSize++;
    return;
}

HASHNODE* GetLastNode(HASHNODE* currentNode)
{
    if(currentNode->next == NULL)
    {
        return currentNode;
    }
    else
    {
        return GetLastNode(currentNode->next);
    }
}

bool CheckHashTable(const char* string)
{
    unsigned long arrayPos = hash(string);
    if(stuff[arrayPos] == NULL)
    {
        return false;
    }
    HASHNODE* node = stuff[arrayPos];
    while(node != NULL)
    {
        if(strcmp(node->storedString,string) == 0)
        {
            return true;
        }
        node = node->next;
    }
    return false;
}

void ClearNode(HASHNODE* node)
{
    if(node == NULL)
    {
        return;
    }

    if(node->next != NULL)
    {
        ClearNode(node->next);
    }

    free(node->storedString);
    free(node);
    return;
}

