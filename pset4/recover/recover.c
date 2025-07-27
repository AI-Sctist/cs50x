#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define JPEG_BLOCK_SIZE 512

uint8_t JPEG_sign(uint8_t *buff);
void start_writing(FILE *card);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILENAME\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 1;
    }

    uint8_t *buff = malloc(1);
    int progress = 0;

    while (fread(buff, 1, 1, card) == 1)
    {
        if ((progress == 0 && *buff == 0xff) || (progress == 1 && *buff == 0xd8) ||
            (progress == 2 && *buff == 0xff) || (progress == 3 && (*buff & 0xe0) == 0xe0))
        {
            progress++;
        }
        else
        {
            progress = 0;
        }

        if (progress == 4)
        {
            fseek(card, -4, SEEK_CUR);
            start_writing(card);
        }
    }

    free(buff);
    fclose(card);
}

uint8_t JPEG_sign(uint8_t *buff)
{
    return (*buff == 0xff && *(buff + 1) == 0xd8 && *(buff + 2) == 0xff &&
            (*(buff + 3) & 0xe0) == 0xe0);
}

void start_writing(FILE *card)
{
    // The current order of discovered JPEGs
    int order = 0;

    // Prepare before writing to file
    char *fname = malloc(50);
    FILE *image = NULL;
    uint8_t *buff = malloc(JPEG_BLOCK_SIZE);

    while (fread(buff, 4, 1, card) == 1)
    {
        fseek(card, -4, SEEK_CUR);
        if (JPEG_sign(buff))
        {
            if (image != NULL)
            {
                fclose(image);
            }

            sprintf(fname, "%03i.jpg", order++);
            image = fopen(fname, "a");
        }

        fread(buff, JPEG_BLOCK_SIZE, 1, card);
        fwrite(buff, JPEG_BLOCK_SIZE, 1, image);
    }

    free(fname);
    free(buff);
    fclose(image); // The last jpeg file has not been close yet
}
