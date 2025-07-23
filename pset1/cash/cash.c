#include <cs50.h>
#include <stdio.h>

int change;       // the given amount of change
int coins_needed; // the minimum coins needed to make the given amount of change

void use_coin(int coin_type)
{
    while (change >= coin_type)
    {
        coins_needed++;
        change -= coin_type;
    }
}

int main(void)
{
    do
    {
        change = get_int("Change owed: ");
    }
    while (change <= 0);

    use_coin(25);
    use_coin(10);
    use_coin(05);
    use_coin(01);

    printf("%i\n", coins_needed);
}
