# Harvard CS50X Problem Set Submission
# Problem Set 6 - Sentimental Mario More
# By Joshua Lehman - May 7, 2024


def print_row(spaces, bricks):
    for i in range(spaces-1):
        print(" ", end="")

    for j in range(bricks):
        print("#", end="")

    print("  ", end="")

    for k in range(bricks):
        print("#", end="")

    print()


def get_height():
    while True:
        try:
            n = int(input("Height:"))
            if n >= 1 and n <= 8:
                return n
            else:
                print("Height must be between 1 and 8")
        except ValueError:
            print("Please enter a valid integer")


def main():
    height = get_height()

    for i in range(height):
        print_row(height-i, i+1)


main()
