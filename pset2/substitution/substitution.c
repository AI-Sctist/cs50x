#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool alphabetic(string s);
bool repeatitive(string s);

int main(int argc, string argv[])
{
    // check the correctness of the command and its arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1; // return error code
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1; // return error code
    }
    if (!alphabetic(argv[1]))
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1; // return error code
    }
    if (repeatitive(argv[1]))
    {
        printf("Key must not contain repeated characters.\n");
        return 1; // return error code
    }

    // secret key to encrypt message
    string key = argv[1];
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        key[i] = tolower(key[i]);
    }

    // get user's message
    string text = get_string("plaintext:  ");

    // encrypt message by mapping each letter into another one
    // according to the instruction from the key
    printf("ciphertext: ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (islower(text[i]))
        {
            int id = text[i] - 'a';
            printf("%c", key[id]);
        }
        else if (isupper(text[i]))
        {
            int id = text[i] - 'A';
            printf("%c", toupper(key[id]));
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}

bool alphabetic(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
    }
    return true;
}

bool repeatitive(string s)
{
    // array to mark appeared letters
    bool ex[26];
    memset(ex, false, sizeof(ex));

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (ex[tolower(s[i]) - 'a'])
        {
            return true;
        }
        // mark character as appeared
        ex[tolower(s[i]) - 'a'] = true;
    }
    return false;
}
