// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one ");
        printf("uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    // Check if the password has at least one:
    // - Uppercase letter
    // - Lowercase letter
    // - Number
    // - Symbol

    bool upp = false;
    bool low = false;
    bool num = false;
    bool sym = false;

    for (int i = 0, n = strlen(password); i < n; i++)
    {
        if (isupper(password[i]))
        {
            upp = true;
        }
        else if (islower(password[i]))
        {
            low = true;
        }
        else if (isdigit(password[i]))
        {
            num = true;
        }
        else
        {
            sym = true;
        }
    }

    return upp && low && num && sym;
}
