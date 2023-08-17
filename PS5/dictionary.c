// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26;

int countwords = 0;
int hashtable_index = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    hash(word);
    node *tmp = table[hashtable_index];
    while(tmp != NULL)
    {
        if(strcasecmp(tmp->word,word) == 0)
        {
            return true;
        }
        tmp = tmp-> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int first = toupper(word[0]) - 'A';
    int second = 0;
    if(strlen(word)>1)
    {
        second = toupper(word[1]) - 'A';
    }
    hashtable_index = first * 26 + second;
    return hashtable_index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary,"r");
    if(file == NULL)
    {
        return false;
    }
    char *line = malloc(LENGTH);

    while(fgets(line,LENGTH,file))
    {
        node *n = malloc(sizeof(node));

        if(n == NULL)
        {
            return false;
        }
        
        *(line+strlen(line)-1) = '\0';
        hash(line);

        strcpy(n->word,line);
        n->next = table[hashtable_index];

        table[hashtable_index] = n;

        countwords++;

    }
    free(line);
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return countwords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        if(table[i] == NULL)
        {
            continue;
        }

        node *cursor = table[i];
        node *tmp = cursor;
        
        while(cursor != NULL)
        {
            free(cursor);
            cursor = tmp->next;
            tmp = cursor;
        }
    }
    return true;
}
