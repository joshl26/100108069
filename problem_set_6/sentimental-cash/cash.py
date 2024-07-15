# Harvard CS50X Problem Set Submission
# Problem Set 6 - Sentimental Cash
# By Joshua Lehman - May 7, 2024

from cs50 import get_float


def calculate_change(cents, centsPer):
    counter = 0

    while cents >= centsPer:
        counter += 1
        cents = cents - centsPer
        # print(f"Cents: {cents}")
        # print(f"Counter: {counter}")
    return counter


def main():

    changeCount = 0
    centsPerQuarter = 25
    centsPerDime = 10
    centsPerNickel = 5
    centsPerPenny = 1

    # Prompt user for change owed

    while True:
        cents = get_float("Change owed: ") * 100
        if cents > 0:
            break

    # Calculate how many quarters you should give a customer
    quarters = calculate_change(cents, centsPerQuarter)

    # Calculate how many quarters you should give a customer
    cents = cents - (quarters * centsPerQuarter)

    # Calculate how many quarters you should give a customer
    dimes = calculate_change(cents, centsPerDime)

    # Calculate how many quarters you should give a customer
    cents = cents - (dimes * centsPerDime)

    # Calculate how many quarters you should give a customer
    nickels = calculate_change(cents, centsPerNickel)

    # Calculate how many quarters you should give a customer
    cents = cents - (nickels * centsPerNickel)

    # Calculate how many quarters you should give a customer
    pennies = calculate_change(cents, centsPerPenny)

    # Calculate how many quarters you should give a customer
    cents = cents - (pennies * centsPerPenny)

    # Sum the number of quarters, dimes, nickels and pennies
    changeCount = quarters + nickels + dimes + pennies

    print(f"{changeCount}\n")


main()
