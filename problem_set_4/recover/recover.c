// Harvard CS50X Problem Set Submission
// Problem Set 4 - Recover
// By Joshua Lehman - May 4, 2024

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument for the filename
    if (argc != 2)
    {
        printf("Usage: recover [filename]\n");
    }

    // Remember filenames
    char *infile = argv[1];

    // Open the memory card
    FILE *inputr = fopen(infile, "r");
    FILE *image = NULL;

    if (inputr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // Create a buffer
    uint8_t buffer[512];
    int counter = 0;

    // While theres still data left to read from the memory card
    while (fread(buffer, 1, 512, inputr) > 0)
    {

        // int blocks = fread(buffer, 1, 512, inputr);

        // printf("%i\n", blocks);

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {

            if (image != NULL)
            {
                fclose(image);
            }

            // Create individual jpegs from the data
            char *filename;

            // ###.jgp\0 - 8 char x 4bytes =  32 bytes for the name
            char filenameBuffer[8];

            // printf("Counter: %i\n", counter);

            sprintf(filenameBuffer, "%03i.jpg", counter);

            // printf("%s\n", filenameBuffer);
            image = fopen(filenameBuffer, "w");

            if (image == NULL)
            {
                printf("Could not create image.");
                return 2;
            }
            counter += 1;
        }

        if (image != NULL)
        {
            fwrite(buffer, 512, 1, image);
        }
    }

    if (image != NULL)
    {
        fclose(image);
    }

    fclose(inputr);

    return 0;
}
