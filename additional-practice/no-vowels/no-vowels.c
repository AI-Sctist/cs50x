// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Replace vowels in a word with numbers
string replace(string s);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1; // Error code
    }

    // Argument argv[1] is the word needing to be converted
    printf("%s\n", replace(argv[1]));
}

string replace(string s)
{
    // 'a' becomes '6'
    // 'e' becomes '3'
    // 'i' becomes '1'
    // 'o' becomes '0'
    // Other ones are unchanged
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        switch (s[i])
        {
            case 'a':
                s[i] = '6';
                break;

            case 'e':
                s[i] = '3';
                break;

            case 'i':
                s[i] = '1';
                break;

            case 'o':
                s[i] = '0';
                break;

            default:
                break;
        }
    }

    return s;
}
