#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// check whether s is a number or not
bool valid_encryption_key(string s);

// convert from string to int
int to_int(string s);

int main(int argc, string argv[])
{
    // check the correctness of the command and its arguments
    if (argc != 2 || !valid_encryption_key(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1; // return error code
    }

    // secret key to encrypt message
    int key = to_int(argv[1]);

    // get user's message
    string text = get_string("plaintext:  ");

    // encrypt messages by rotating each letter by "key" positions
    printf("ciphertext: ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (islower(text[i]))
        {
            int p = ((text[i] - 'a') + key) % 26;
            printf("%c", 'a' + p);
        }
        else if (isupper(text[i]))
        {
            int p = ((text[i] - 'A') + key) % 26;
            printf("%c", 'A' + p);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n"); // make new line for CLI
}

bool valid_encryption_key(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

int to_int(string s)
{
    int interger = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        int digit = s[i] - '0';
        interger = interger * 10 + digit;
    }
    return interger;
}
