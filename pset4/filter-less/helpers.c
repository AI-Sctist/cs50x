#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round(image[i][j].rgbtRed / 3.0 + image[i][j].rgbtGreen / 3.0 +
                            image[i][j].rgbtBlue / 3.0);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepia_red = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen +
                                  0.189 * image[i][j].rgbtBlue);
            int sepia_green = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen +
                                    0.168 * image[i][j].rgbtBlue);
            int sepia_blue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen +
                                   0.131 * image[i][j].rgbtBlue);

            image[i][j].rgbtRed = (sepia_red < 255 ? sepia_red : 255);
            image[i][j].rgbtGreen = (sepia_green < 255 ? sepia_green : 255);
            image[i][j].rgbtBlue = (sepia_blue < 255 ? sepia_blue : 255);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j * 2 < width; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Relative neighboring position to a 3x3 square center
    int di[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    int dj[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

    RGBTRIPLE blured[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sr = 0, sg = 0, sb = 0; // Total RGB-channel values of neighboring pixels
            int cnt = 0;                // Count neighboring pixels insided image

            for (int k = 0; k < 9; k++)
            {
                int inside =
                    (0 <= i + di[k] && i + di[k] < height && 0 <= j + dj[k] && j + dj[k] < width);

                if (inside)
                {
                    sr += image[i + di[k]][j + dj[k]].rgbtRed;
                    sg += image[i + di[k]][j + dj[k]].rgbtGreen;
                    sb += image[i + di[k]][j + dj[k]].rgbtBlue;

                    cnt++;
                }
            }

            blured[i][j].rgbtRed = (int) round(1.0 * sr / cnt);
            blured[i][j].rgbtGreen = (int) round(1.0 * sg / cnt);
            blured[i][j].rgbtBlue = (int) round(1.0 * sb / cnt);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blured[i][j].rgbtRed;
            image[i][j].rgbtGreen = blured[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blured[i][j].rgbtBlue;
        }
    }
    return;
}
