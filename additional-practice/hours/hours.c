#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        printf("Enter T for total hours, A for average hours per week: ");
        output = toupper(get_char(""));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
    // Total hours of learning CS50
    int total = 0;
    for (int i = 0; i < weeks; i++)
    {
        total += hours[i];
    }

    // Average hours of learning CS50 per week
    float avg = (float) total / weeks;

    if (output == 'T')
    {
        return total;
    }
    else
    {
        return avg;
    }
}
