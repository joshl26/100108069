// Harvard CS50X Problem Set Submission
// Problem Set 5 - Spelling
// By Joshua Lehman - May 25, 2024

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

// Choose number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Number of words in dictionary
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // assume word will always be strings containing only Uppercase or Lowercase letters and
    // and possibly apostrophes.
    // must be case in-sensitive i.e. if we search foo, Foo, FOO... its the same
    // should only return true for words actually in the dictionary
    // possessives are not allowed unless in dictionary i.e. given foo's return
    // false if foo's not in dictionary
    // assume any dictionary to be sorted in order, one word per line ending with \n
    // assume dictionary will contain at least one word, and no word will be longer than LENGTH
    // assume no word will appear more than once
    // assume each word will contain only lower case letters and possibly apostrophes
    // assume no word will start with an apostrophe

    // HASH the word to obtain its hash value
    unsigned int hash_value = hash(word);

    char lower_word[LENGTH + 1];
    for (int i = 0; i < strlen(word); i++)
    {
        lower_word[i] = tolower(word[i]);
    }

    lower_word[strlen(word)] = '\0';

    // Search the hash table at the location specified by the words hash value

    node *cursor = table[hash_value];
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, lower_word) == 0)
        {
            // Return true if the word is found
            return true;
        }
        cursor = cursor->next;
    }

    // Return false if no word is found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function
    // return toupper(word[0]) - 'A';

    // consider using a hash function that uses a sum of ASCII values or the length of the word
    // a good hash reduces collisions and has a (mostly) even distribution across has table
    // buckets

    unsigned long hash = 5381;

    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *source = fopen(dictionary, "r");

    if (source == NULL)
    {
        unload();
        return false;
    }

    char word[LENGTH + 1];

    // Read each word in the file
    // Add each word to the hash table
    while (fscanf(source, "%s", word) != EOF)
    {
        // Create space for a new hash table node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        // Copy the word into the new node
        strcpy(new_node->word, word);
        new_node->next = NULL;

        // Hash the word to obtain its value
        unsigned int hash_value = hash(word);

        // Insert the new node into the hash table (using the index specified by its hash value)
        new_node->next = table[hash_value];
        table[hash_value] = new_node;

        // Increase the word count
        word_count++;
    }

    // Close the dictionary file
    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // BE sure to free in unload any memory that you allocated in load!
    // make use of valgrind to analyze code for possible memory leaks
    // valgrind ./speller texts/cat.txt

    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
