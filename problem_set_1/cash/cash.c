#include <cs50.h>
#include <stdio.h>

// Harvard CS50X Problem Set Submission
// Problem Set 1 - Cash
// By Joshua Lehman - April 20, 2024

int calculate_change(int cents, int centsPer);

int main(void)
{
    // Prompt the user to enter the change required, in cents
    int cents;
    int changeCount;
    int centsPerQuarter = 25;
    int centsPerDime = 10;
    int centsPerNickel = 5;
    int centsPerPenny = 1;

    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // Calculate how many quarters you should give a customer
    int quarters = calculate_change(cents, centsPerQuarter);

    // Subtract the value of those quarters from cents
    cents = cents - (quarters * centsPerQuarter);

    // Calculate how many dimes you should give a customer
    int dimes = calculate_change(cents, centsPerDime);

    // Subtract the value of those dimes from remaining cents
    cents = cents - (dimes * centsPerDime);

    // Calculate how many nickels you should give a customer
    int nickels = calculate_change(cents, centsPerNickel);

    // Subtract the value of those nickels from remaining cents
    cents = cents - (nickels * centsPerNickel);

    // Calculate how many pennies you should give a customer
    int pennies = calculate_change(cents, centsPerPenny);

    // Subtract the value of those pennies from remaining cents
    cents = cents - (pennies * centsPerPenny);

    // Sum the number of quarters, dimes, nickels and pennies
    changeCount = quarters + dimes + nickels + pennies;

    // Print the sum
    printf("%i\n", changeCount);
}

int calculate_change(int cents, int centsPer)
{
    // calculate how many quarters to give to the customer
    int counter = 0;

    while (cents >= centsPer)
    {
        counter++;
        cents = cents - centsPer;
    }
    return counter;
}
