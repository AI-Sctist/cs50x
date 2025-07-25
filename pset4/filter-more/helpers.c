#include "helpers.h"
#include <math.h>

#define min(i, j) (i <= j ? i : j)

// Boolean func to check if (i, j) is inside the given boundaries
uint8_t inside(int i, int j, int height, int width)
{
    return (0 <= i && i < height && 0 <= j && j < width);
}

// The nearest number to the square root of the sum of the squares of two numbers
// The character 'r' is short for "round"
int rHypot(int a, int b)
{
    return round(sqrt(a * a + b * b));
}

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
    // Relative position to the center of a 3x3 square
    const int di[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    const int dj[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

    RGBTRIPLE blured[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sr = 0, sg = 0, sb = 0;
            int cnt = 0;

            for (int k = 0; k < 9; k++)
            {
                if (inside(i + di[k], j + dj[k], height, width))
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
            image[i][j] = blured[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Relative position to the center of a 3x3 square
    const int di[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    const int dj[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

    // The weight array for calculating Gx and Gy in Sobel operator
    // https://en.wikipedia.org/wiki/Sobel_operator
    const int Wx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    const int Wy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Gx and Gy for RGB color channels
            int GxR = 0, GyR = 0;
            int GxG = 0, GyG = 0;
            int GxB = 0, GyB = 0;

            for (int k = 0; k < 9; k++)
            {
                if (inside(i + di[k], j + dj[k], height, width))
                {
                    // Red channel
                    GxR += (int) image[i + di[k]][j + dj[k]].rgbtRed * Wx[k];
                    GyR += (int) image[i + di[k]][j + dj[k]].rgbtRed * Wy[k];

                    // Green channel
                    GxG += (int) image[i + di[k]][j + dj[k]].rgbtGreen * Wx[k];
                    GyG += (int) image[i + di[k]][j + dj[k]].rgbtGreen * Wy[k];

                    // Blue channel
                    GxB += (int) image[i + di[k]][j + dj[k]].rgbtBlue * Wx[k];
                    GyB += (int) image[i + di[k]][j + dj[k]].rgbtBlue * Wy[k];
                }
            }

            tmp[i][j].rgbtRed = min(255, rHypot(GxR, GyR));
            tmp[i][j].rgbtGreen = min(255, rHypot(GxG, GyG));
            tmp[i][j].rgbtBlue = min(255, rHypot(GxB, GyB));
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}
