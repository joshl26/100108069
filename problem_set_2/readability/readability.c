// Harvard CS50X Problem Set Submission
// Problem Set 2 - Readability
// By Joshua Lehman - May 06, 2024

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);

int count_words(string text);

int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // printf("Letters: %i\n", letters);
    // printf("Words: %i\n", words);
    // printf("Sentences: %i\n", sentences);

    // Compute the Coleman-Liau index
    float L = (letters / (float) words) * 100;

    // printf("L: %f\n", L);

    float S = (sentences / (float) words) * 100;

    // printf("S: %f\n", S);

    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    // Print the grade level

    if (index < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }

    if (index > 16)
    {
        printf("Grade 16+\n");
        return 0;
    }

    printf("Grade %i\n", index);

    return 0;
}

int count_letters(string text)
{

    int letter_count = 0;

    // Return the number of letters in text
    int length = strlen(text);

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]) != 0)
        {
            letter_count += 1;
        }
    }

    // printf("Letter Count: %i\n", letter_count);

    return letter_count;
}

int count_words(string text)
{

    int word_count = 0;
    int letter_count = 0;

    // TODO a word is:
    // TODO any sequence of characters separated by a blank char
    // TODO a hyphenated word is valid sister-in-law
    // TODO will not have multiple spaces in a row

    int length = strlen(text);

    if (length > 0)
    {
        word_count = 1;
    }

    for (int i = 0; i < length; i++)
    {
        if (text[i] == 32 && text[i + 1] != 32)
        {
            word_count += 1;
        }
        // printf("%i", text[i]);
    }

    // Return the number of words in text
    //
    // printf("Word Count: %i\n", word_count);

    return word_count;
}

int count_sentences(string text)
{
    // TODO A sentence is any sequence of characters that ends with . ! or ?

    // TODO Return the number of sentences in text

    int sentence_count = 0;

    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sentence_count += 1;
        }
    }

    // printf("%i\n", sentence_count);

    return sentence_count;
}
