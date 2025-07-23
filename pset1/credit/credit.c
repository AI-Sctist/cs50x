#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

bool Luhn_pretest(string number)
{
    int sum = 0;
    int cnt = 0;
    int len = strlen(number);

    for (int i = 0; i < len; i++)
    {
        int p = (i % 2 + 1) * (number[len - i - 1] - '0');
        sum += (p % 10) + (p / 10);
    }

    return sum % 10 == 0;
}

int main(void)
{
    string number = get_string("Number: ");
    if (!Luhn_pretest(number))
    {
        printf("INVALID\n");
        return 0;
    }

    int len = strlen(number);
    if (len == 15 && number[0] == '3' && (number[1] == '4' || number[1] == '7'))
    {
        printf("AMEX\n");
    }
    else if (len == 16 && number[0] == '5' && number[1] > '0' && number[1] < '6')
    {
        printf("MASTERCARD\n");
    }
    else if ((len == 13 || len == 16) && number[0] == '4')
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
