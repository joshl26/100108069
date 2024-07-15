// Harvard CS50X Problem Set Submission
// Problem Set 4 - Volume
// By Joshua Lehman - May 3, 2024

// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float volume_factor = atof(argv[3]);

    // Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // Read samples from input file and write updated data to output file
    int16_t wav_buffer;

    // Read a single wav sample into buffer while fwrite returns a value other
    // than 0 which indicates there are samples yet to read.
    while (fread(&wav_buffer, sizeof(int16_t), 1, input))
    {
        // Update the volume of the current wav sample
        wav_buffer *= volume_factor;

        // Write updated wav sample to a new file
        fwrite(&wav_buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);

    return 0;
}
