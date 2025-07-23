#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get user name
    string name = get_string("What's your name? ");

    // say hello to user
    printf("hello, %s\n", name);
}
