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

    //Make sure that the index cannot overrun the array bounds
    return h % OXFORD_WORDS;
}

void AddToHashTable(char* string)
{
    //Get the correct position in the hashtable
    unsigned long arrayPos = hash(string);

    //Create the hashnode for the new string (with data)
    HASHNODE* nodePtr = malloc(sizeof(HASHNODE));
    nodePtr->next = NULL;
    nodePtr->storedString = malloc(strlen(string)+1);
    strcpy(nodePtr->storedString, string);

    //Add the new hashnode in its appropriate place in the linked list
    if(hashTable[arrayPos] == NULL)
    {
        hashTable[arrayPos] = nodePtr;
    }
    else
    {
        HASHNODE* lastNode = GetLastNode(hashTable[arrayPos]);
        lastNode->next = nodePtr;
    }

    //Keep track of how large our hash list is
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

    //If no linked list exists, return null
    if(hashTable[arrayPos] == NULL)
    {
        return false;
    }

    //Get the first node of the linked list and then iterate through the list checking for the desired value
    HASHNODE* node = hashTable[arrayPos];
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