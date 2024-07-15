// Harvard CS50X Problem Set Submission
// Problem Set 4 - Filter
// By Joshua Lehman - May 3, 2024

#include "helpers.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    // printf("Height: %i\n", height);
    // printf("Width: %i\n", width);

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // printf("%i,", image[i][j].rgbtRed);
            // printf("%i,", image[i][j].rgbtGreen);
            // printf("%i - ", image[i][j].rgbtBlue);

            // Take average of red, green and blue pixels.
            int average = (int) round(
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Assign the averaged value and assign to each pixel in the image.
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Calculate sepia color values
            int sepiaRed = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) +
                                 (.189 * image[i][j].rgbtBlue));
            int sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) +
                                   (.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) +
                                  (.131 * image[i][j].rgbtBlue));

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Assign newly calculated color to individual pixels in the image
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    // temp[0] = malloc(sizeof(RGBTRIPLE)*width*height);

    printf("%lu\n", sizeof(RGBTRIPLE) * height);

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];

            image[i][j] = image[i][width - 1 - j];

            image[i][width - 1 - j] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Create a copy
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // printf("%i\n", copy[0][100].rgbtBlue);

    // Apply blur effect
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red_total = 0;
            int green_total = 0;
            int blue_total = 0;
            float counter = 0.0;

            // Check all pixels surrounding the current pixel where applicable
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int ik = i + k;
                    int jl = j + l;

                    // Check edge cases
                    if (ik >= 0 && ik < height && jl >= 0 && jl < width)
                    {
                        red_total += copy[ik][jl].rgbtRed;
                        green_total += copy[ik][jl].rgbtGreen;
                        blue_total += copy[ik][jl].rgbtBlue;
                        counter++;
                    }
                }
            }

            // Copy blurred pixel values over to image
            image[i][j].rgbtRed = (int) round(red_total / counter);
            image[i][j].rgbtGreen = (int) round(green_total / counter);
            image[i][j].rgbtBlue = (int) round(blue_total / counter);
        }
    }

    return;
}
