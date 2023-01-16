// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Word count from dictionary
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain hash value
    int hashv = hash(word);

    // Access linked list at that index in the hash table
    node *cursor = table[hashv];

    // Traverse linked list, looking for the word (strcasecmp)
    // Start with cursor set to the first item in linked list.
    // re-run loop to check the rest of the list
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;

// Keep moving cursor until you get to NULL, checking each node for the word

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function, toupper() converts to uppercase
    // if word length is 1 char
    unsigned int hash = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        hash += tolower(word[i]);
    }

    return hash % N;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    //printf("loaded\n");
    FILE *file = fopen(dictionary, "r");   // open dictionary file

    if (file == NULL)    // check file opened ok
    {
        return false;
    }

    char dword[LENGTH + 1]; // create a place to put the word

    while (fscanf(file, "%s", dword) != EOF)  // Read strings frome file one at a time, runs until fscan returns EOF
    {

        node *n = malloc(sizeof(node));  // Create a new node for each word
        if (n == NULL)  // if malloc was successful
        {
            return false;
        }

        // Copy scanned word to node
        strcpy(n->word, dword);

        // Hash word to obtain a hash value
        int hv = hash(dword);

        // Insert node into hash table at that location
        if (table[hv] == NULL)   // if list location doesn't contain data
        {
            n->next = NULL;

        }
        else  // insert into linked list
        {
            n->next = table[hv];
        }

        table[hv] = n;

        word_count++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else  false
bool unload(void)
{

    // loop over table
    for (int i = 0; i < N; i++)
    {
        // point to first node in array
        node *cursor = table[i];

        while (cursor != NULL)
        {
            // use a variable to track the next node to free
            node *tmp = cursor;

            // move cursor pointer to next node
            cursor = cursor->next;

            // free the memory from tmp
            free(tmp);
        }

        // if cursor is at the end return true
        if ((i == N - 1) && (cursor == NULL))
        {
            return true;
        }

    }

    return false;
}
