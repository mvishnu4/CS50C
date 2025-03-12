#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = lround((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen)/3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
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
            int speciaRed = lround(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int speciaGreen = lround(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int speciaBlue = lround(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtBlue = speciaBlue < 255 ? speciaBlue : 255;
            image[i][j].rgbtGreen = speciaGreen < 255 ? speciaGreen : 255;
            image[i][j].rgbtRed= speciaRed < 255 ? speciaRed : 255;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
        for (int k = 0; k < width; k++)
        {
            image[i][k].rgbtRed = copy[i][width - k - 1].rgbtRed;
            image[i][k].rgbtBlue = copy[i][width - k - 1].rgbtBlue;
            image[i][k].rgbtGreen = copy[i][width - k - 1].rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                int avgGreen = lround((copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen) / 4);
                int avgBlue = lround((copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue) / 4);
                int avgRed = lround((copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed) / 4);
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            if (i == 0 && j == width - 1)
            {
                int avgGreen = lround((copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen) / 4);
                int avgBlue = lround((copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue) / 4);
                int avgRed = lround((copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed) / 4);
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
            }
            if (i == 0 && j > 0 && j < width - 1)
            {
                int avgGreen = lround((copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen) / 6);
                int avgBlue = lround((copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue) / 6);
                int avgRed = lround((copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed) / 6);
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
            }
            if (j == 0 && i > 0 && i < height -1)
            {
                int avgGreen = lround((copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen) / 6);
                int avgBlue = lround((copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue) / 6);
                int avgRed = lround((copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j].rgbtBlue + copy[i][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed) / 6);
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtRed = avgRed;
            }
            if (i != 0 && j != 0)
            {
                int avgRed = lround((copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed) / 9);
                int avgBlue = lround((copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue) / 9);
                int avgGreen = lround((copy[i-1][j-1].rgbtGreen+ copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen) / 9);
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtBlue = avgBlue;
            }
            if (j == width -1 && i > 0 && i < height - 1)
            {
                int avgGreen = lround((copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen) / 6);
                int avgBlue = lround((copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue) / 6);
                int avgRed = lround((copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed) / 6);
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtRed = avgRed;
            }
            if (i == height - 1 && j > 0 && j < width - 1)
            {
                int avgGreen = lround((copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen) / 6);
                int avgBlue = lround((copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue) / 6);
                int avgRed = lround((copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j].rgbtRed + copy[i][j+1].rgbtRed) / 6);
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtRed = avgRed;

            }
            if (i == height - 1 && j == 0)
            {
                int avgGreen = lround((copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen) / 4);
                int avgBlue = lround((copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue) / 4);
                int avgRed = lround((copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j].rgbtRed + copy[i][j+1].rgbtRed) / 4);
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtRed = avgRed;

            }
            if (i == height - 1 && j == width -1 )
            {
                int avgGreen = lround((copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j].rgbtGreen) / 4);
                int avgBlue = lround((copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j].rgbtBlue) / 4);
                int avgRed = lround((copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j].rgbtRed) / 4);
                image[i][j].rgbtGreen = avgGreen;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtRed = avgRed;
            }
        }
    }
    return;
}
