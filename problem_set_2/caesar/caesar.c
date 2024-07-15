// Harvard CS50X Problem Set Submission
// Problem Set 2 - Caesar
// By Joshua Lehman - May 6, 2024

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string digits);

char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Make sure the program is run with single command line

    // printf("%i \n", argc);

    // printf("argv[0]: %s\n", argv[0]);

    // printf("argv[1]: %s\n", argv[1]);

    // printf("argv[2]: %s\n", argv[2]);

    if (argc > 2)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }
    else if (argc <= 1)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }

    // Make sure every character in arg[1] is a digit

    // Returns a 1 for true and 0 for false
    bool onlyDigits = only_digits(argv[1]);

    // printf("%d\n", onlyDigits);

    // Convert argv[1] from a `string` to an `int`

    int convertedDigits = 0;

    if (onlyDigits == 1)
    {
        convertedDigits = atoi(argv[1]);
    }
    else
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }

    // printf("%i\n", convertedDigits);

    // Prompt user for plaintext

    string plainText = get_string("Plaintext: ");

    // printf("%s\n", plainText);

    int plainTextLength = strlen(plainText);

    char cipherText[plainTextLength];

    // For each character in the plaintext:

    for (int i = 0; i < plainTextLength; i++)
    {

        cipherText[i] = 0;

        char convertedChar;

        char testChar = plainText[i];

        // Is character alphabetical? Returns 1 for true and 0 for false
        int isAlpha = isalpha(testChar);

        // Rotate the character if it's a letter
        if (isAlpha > 0)
        {
            convertedChar = rotate(plainText[i], convertedDigits);

            // printf("%c\n", convertedChar);
        }
        else
        {
            convertedChar = plainText[i];
            // printf("%c\n", convertedChar);
        }

        char temp[2];

        temp[0] = convertedChar;
        temp[1] = '\0';

        strncat(cipherText, temp, 2);

        //    printf("%s \n", strcat(cipherText, temp));
        //    printf("ciphertext: %s \n", cipherText);
    }

    printf("ciphertext: %s\n", cipherText);

    return 0;
}

bool only_digits(string x)
{
    // printf("%c\n",x[0]);

    // printf("%s\n",x);

    int strLength = strlen(x);

    // printf("%i\n", strLength);

    // y = isdigit(x);

    // printf("%b\n ", y)

    bool flag = true;

    for (int i = 0; i < strLength; i++)
    {
        int isDigit = isdigit(x[i]);

        // printf("%i\n", isdigit(x[i]));
        // printf("%c\n", x[i]);

        if (isDigit == 0)
        {
            flag = false;
        }
    }

    return flag;
}

char rotate(char c, int n)
{
    // printf("%c\n", c );

    // printf("%i\n", c );

    // printf("%i\n", n );

    // Check to see if n%25 has a remainder, if it does that becomes n

    char start;

    int number_letters = 26;

    int remainder = n % number_letters;

    // printf("remainder: %i\n", remainder);

    if (remainder > 0)
    {
        n = remainder;
    }

    if (isupper(c) > 0)
    {
        start = 'A';
    }

    if (islower(c) > 0)
    {
        start = 'a';
    }

    if (isalnum(c) == 0)
    {
        return c;
    }

    int integerValue = (int) (c - start);

    integerValue += n;

    // printf("%i\n", integerValue);

    int decryptedChar = start + (integerValue % 26);

    // printf("%c\n", decryptedChar );

    return decryptedChar;
}
