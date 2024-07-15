#include <cs50.h>
#include <stdio.h>

// Harvard CS50X Problem Set Submission
// Problem Set 1 - Mario
// By Joshua Lehman - April 20, 2024

void print_row(int spaces, int bricks);

int get_height();

int main(void)
{

    int height = get_height();

    // Print a pyramid of that height
    for (int i = 0; i < height; i++)
    {

        // Print row of bricks
        print_row(height - i, i + 1);
    }
}

void print_row(int spaces, int bricks)
{

    // Print leading blank spaces
    for (int i = 0; i < spaces - 1; i++)
    {
        printf(" ");
    }

    // Print left side section of bricks
    for (int j = 0; j < bricks; j++)
    {
        printf("#");
    }

    // Print two blank spaces between left and right sections
    for (int k = 0; k < 2; k++)
    {
        printf(" ");
    }

    // Print right side section of bricks
    for (int l = 0; l < bricks; l++)
    {
        printf("#");
    }

    printf("\n");
}

int get_height()
{
    // Prompt user to enter a Height
    int n;

    do
    {
        n = get_int("");
    }
    while (n < 1 || n > 8);

    return n;
}
