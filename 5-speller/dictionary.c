// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

void hashdictionary(void);
// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];


char start[143094];
char end[143094];
int i;
int w;
int hashdict[143094];
int hashvalue;
int len;
int dictcount;
int bytes;
FILE *openDict = NULL;
// Returns true if word is in dictionary, else false

bool check(const char *word)
{
    int hashed = 0;
    for (int k = 0; k < strlen(word); k++)
    {
        hashed += hash(&word[k]);
    }
    for (int h = 0; h < 143094; h++)
    {
        if (hashed == hashdict[h])
        {
            //printf("..%i..%c%c%c%c %i %i,", h,start[h], toupper(word[0]), end[h], toupper(word[strlen(word) - 1]), hashed, hashdict[h]);
            if (start[h] == toupper(word[0]) && end[h] == toupper(word[strlen(word) - 1]))
            {
                return true;
                break;
            }
        }
    }
    return false; // 113
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    /*int sum = 0;
    for (int j = 0; word[j] != '\0'; j++)
    {
        sum += toupper(word[j]);
    }
    
    return sum % 26;*/
    return toupper(word[0]) - 'A' + 1;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{//"\(dictionary)"
    // opened dictionary to the memory
    openDict = fopen("/Users/madarapuvishnuvardhanrao/Desktop/Desktop/cs50.h Xcode and CS50/speller/speller/dictionaries/large", "r");
    if (openDict == NULL)
    {
        return false;
    }
    hashdictionary();
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return dictcount; // 145
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //printf("%i %li", (bytes + dictcount), ftell(openDict));
    if (ftell(openDict) == (bytes + dictcount))
    {
        fclose(openDict);
        return true;
    }
    return false;
}

void hashdictionary(void)
{
     // declared char to read each character from dict
    char c;
    // counting no of words using new line escape sequence character(\n)
    int wordc = 0;
    // counting no of letters
    int lettercount = 0;
    i = 0;
    w = 0;
    hashvalue = 0;
    start[0] = 'A';
    end[0] = 'A';
    bool newword = false;
    char p = '\0';
    while (fread(&c, sizeof(char), 1, openDict))
    {
        if (c == '\n')
        {
            wordc += 1;
            dictcount = wordc;
            hashdict[w] = hashvalue;
            w++;
            newword = true;
            if (wordc > 2)
            {
                end[wordc - 1] = toupper(p);
            }
        }
        else
        {
            if (newword)
            {
                start[wordc] = toupper(c);
                newword = false;
                hashvalue = 0;
            }
            lettercount += 1;
            bytes = lettercount;
            hashvalue += hash(&c);
            p = c;
        }
    }
}
