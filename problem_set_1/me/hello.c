#include <cs50.h>
#include <stdio.h>

// Harvard CS50X Problem Set Submission
// Problem Set 1 - Hello, It's Me
// By Joshua Lehman - April 11, 2024

int main(void)
{
    string username = get_string("What's your name?");

    printf("hello, %s\n", username);
}
