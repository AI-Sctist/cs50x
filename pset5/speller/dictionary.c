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

// TODO: Choose number of buckets in hash table_(26^5)
const unsigned int BUCKET_COUNT = 11881376;

// Return value for size() function
unsigned int WORD_COUNT = 0;

// Hash table
node *table[BUCKET_COUNT];

// Helper functions
int compare(const char *s1, const char *s2);
bool append(unsigned int hash_code, const char *word);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int hash_code = hash(word);
    node *ptr = table[hash_code];

    while (ptr != NULL)
    {
        int result = compare(word, ptr->word);
        if (result == 0)
        {
            return true;
        }

        // Branch and bound: since the linked list in a bucket is in decreasing order,
        // if the current comparing word is smaller than the given word, then its
        // following words must also be smaller than the given word, so they cannot be
        // equal to the given word.
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
    unsigned int hash_code = 0;

    int index = 0;
    int len = strlen(word);

    for (int i = 0; i < 5; i++, index++)
    {
        while (index < len && word[index] == '\'')
        {
            index++;
        }

        hash_code *= 26;
        if (index < len)
        {
            hash_code += toupper(word[index]) - 'A';
        }
    }
    return hash_code;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < BUCKET_COUNT; i++)
    {
        table[i] = NULL;
    }

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Add two bytes for the newline char ('\n') and the null terminator ('\0')
    char word[LENGTH + 2];

    while (fgets(word, LENGTH + 1, dict) != NULL)
    {
        // Remove the newline char at the end
        word[strcspn(word, "\n")] = '\0';

        // strlen(word) == 0 means it's at the end of file (blank line), my bad :((
        if (strlen(word) > 0)
        {
            bool success = append(hash(word), word);
            if (!success)
            {
                fclose(dict);
                return false;
            }
        }
    }

    fclose(dict);

    // Successfull loading
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return WORD_COUNT;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < BUCKET_COUNT; i++)
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

//============================================================//
//                      HELPER FUNCTIONS                      //
//============================================================//

// Returns -1 if s1 < s2, 0 if s1 == s2, otherwise returns 1
int compare(const char *s1, const char *s2)
{
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    int lim = (l1 < l2) ? l1 : l2;

    for (int i = 0; i < lim; i++)
    {
        if (tolower(s1[i]) < tolower(s2[i]))
        {
            return -1;
        }
        else if (tolower(s1[i]) > tolower(s2[i]))
        {
            return 1;
        }
    }
    return (l1 == l2) ? 0 : ((l1 < l2) ? -1 : 1);
}

// Append a new word to the hash table
bool append(unsigned int code, const char *word)
{
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        return false;
    }

    strcpy(new_node->word, word);
    new_node->next = (table[code] == NULL) ? NULL : table[code];

    WORD_COUNT++;
    table[code] = new_node;

    // Successfull appending
    return true;
}
