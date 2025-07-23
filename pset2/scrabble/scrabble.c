#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// letter scores
const int scores[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                        1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int score(string word);

int main(void)
{
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    int diff = score(player1) - score(player2);

    if (diff > 0)
    {
        printf("Player 1 wins!\n");
    }
    else if (diff < 0)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int score(string word)
{
    int score = 0;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isalpha(word[i]))
        {
            score += scores[tolower(word[i]) - 'a'];
        }
    }
    return score;
}
