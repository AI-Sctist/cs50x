#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]) && input[i] != '+')
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int number = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        number = number * 10 + (input[i] - '0');
    }

    return number;
}
