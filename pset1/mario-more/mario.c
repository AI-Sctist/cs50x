#include <cs50.h>
#include <stdio.h>

void print_space(int row, int height)
{
    for (int i = 0; i < height - (row + 1); i++)
    {
        printf(" ");
    }
}

void print_hash(int row)
{
    for (int i = 0; i < row + 1; i++)
    {
        printf("#");
    }
}

void build_hash_block(int height)
{
    for (int i = 0; i < height; i++)
    {
        print_space(i, height);
        print_hash(i);
        printf("  ");
        print_hash(i);
        printf("\n");
    }
}

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0);

    build_hash_block(height);
}
