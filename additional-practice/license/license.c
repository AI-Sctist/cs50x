#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char (*plates)[7] = calloc(8, 7 * sizeof(char));

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Could not read the file %s.\n", argv[1]);
        return 1;
    }

    int idx = 0;

    while (fread(buffer, 7, 1, infile) == 1)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Save plate number in array
        strcpy(plates[idx], buffer);
        idx++;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }

    free(plates);
    fclose(infile);
}
