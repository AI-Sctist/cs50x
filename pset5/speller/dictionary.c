// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table _ 26^5
const unsigned int SLOTS = 11881376;

// Return value for unsigned in size() function
unsigned int COUNT_WORDS = 0;

// Hash table
node *table[SLOTS];

bool make_node(unsigned int bucket, const char *word)
{
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        return false;
    }
    else
    {
        COUNT_WORDS++;
    }

    strcpy(new_node->word, word);

    if (table[bucket] == NULL)
    {
        new_node->next = NULL;
        table[bucket] = new_node;
    }
    else
    {
        new_node->next = table[bucket];
        table[bucket] = new_node;
    }

    // Successful making new node
    return true;
}

int compare(const char *str1, const char *str2)
{
    int l1 = strlen(str1);
    int l2 = strlen(str2);
    int mn = (l1 < l2) ? l1 : l2;

    for (int i = 0; i < mn; i++)
    {
        if (tolower(*(str1 + i)) < *(str2 + i))
        {
            return -1;
        }
        else if (tolower(*(str1 + i)) > *(str2 + i))
        {
            return 1;
        }
    }

    return (l1 == l2) ? 0 : ((l1 < l2) ? -1 : 1);
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int bucket = hash(word);
    node *ptr = table[bucket];

    while (ptr != NULL)
    {
        int result = compare(word, ptr->word);
        if (result == 0)
        {
            return true;
        }

        /**
         * Look at the way we create the hash table: Take words from the dictionary
         * file that are in increasing order. Whenever taking a new word, insert it
         * at the beginning of the linked-list in a bucket.
         *
         * The order of words in buckets is decreasing order, so if the current word
         * is smaller than the given word, there's no hope for the remaining words to
         * be equal to the given word!
         */
        if (result > 0)
        {
            return false;
        }

        ptr = ptr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int bucket = 0;
    unsigned int len = strlen(word);

    for (int i = 0; i < 5; i++)
    {
        bucket = bucket * 26;
        if (i < len && isalpha(*(word + i)))
        {
            bucket += tolower(*(word + i)) - 'a';
        }
    }
    return bucket;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < SLOTS; i++)
    {
        table[i] = NULL;
    }

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    int index = 0;
    char word[LENGTH + 1];

    while (fread(&word[index], sizeof(char), 1, file))
    {
        if (word[index] != '\n')
        {
            index++;
        }
        else
        {
            word[index] = '\0';
            make_node(hash(word), word);

            // Reset for new word
            index = 0;
        }
    }

    fclose(file);

    // Successfull loading
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return COUNT_WORDS;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < SLOTS; i++)
    {
        node *ptr = table[i];

        while (ptr != NULL)
        {
            node *tmp = ptr->next;
            free(ptr);
            ptr = tmp;
        }
    }

    // Success unloading hash table
    return true;
}
