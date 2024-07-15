// Implements a dictionary's functionality

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO assume word will always be strings containing only Uppercase or Lowercase letters and
    // TODO and possibly apostrophes.
    // TODO must be case in-sensitive i.e. if we search foo, Foo, FOO... its the same
    // TODO should only return true for words actually in the dictionary
    // TODO possessives are not allowed unless in dictionary i.e. given foo's return
    // TODO false if foo's not in dictionary
    // TODO assume any dictionary to be sorted in order, one word per line ending with \n
    // TODO assume dictionary will contain at least one word, and no word will be longer than LENGTH
    // TODO assume no word will appear more than once
    // TODO assume each word will contain only lower case letters and possibly apostrophes
    // TODO assume no word will start with an apostrophe

    // TODO HASH the word to obtain its hash value

    // TODO Search the hash table at the location specified by the words hash value

        // TODO Return true if the word is found

    // TODO Return false if no word is found

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';

    // TODO consider using a hash function that uses a sum of ASCII values or the length of the word
    // TODO a good hash reduces collisions and has a (mostly) even distribution across has table buckets

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if(source == NULL)
    {
        printf("Could not open %s.\n", source);
        return false;
    }

    // TODO Read each word in the file

        // TODO Add each word to the hash table

            // TODO Create space for a new hash table node

            // TODO Copy the word into the new node

            // TODO Hash the word to obtain its value

            // TODO Insert the new node into the hash table (using the index specified by its hash value)

    // Close the dictionary file
    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO Complete the size function
    // TODO CHOOSE ONE OF THE FOLLOWING:
    // TODO Count each word as you load it into the dictionary. Return that count when size is called.
    // TODO Each time size is called iterate through the words in the hash table to count them up. Return that count.
    // TODO Which seems most efficient?

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO BE sure to free in unload any memory that you allocated in load!
    // TODO make use of valgrind to analyze code for possible memory leaks
    // TODO valgrind ./speller texts/cat.txt

    return false;
}
