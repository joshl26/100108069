# Harvard CS50X Problem Set Submission
# Problem Set 6 - DNA
# By Joshua Lehman - May 18, 2024

import csv
import sys

def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Missing command-line argument(s)")
        print("python dna.py [csv file] [text file]")
        sys.exit(1)

    # print(f"hello, {sys.argv[1]}")
    # sys.exit(0)

    # Read database file into a variable
    # with open(sys.argv[1]) as file:
    #     reader1 = csv.DictReader(file)
    #     print(reader1.fieldnames)

    rows = []
    with open(sys.argv[1]) as file:
        reader2 = csv.DictReader(file)
        for row in reader2:
            rows.append(row)

    # Read DNA sequence file into a variable
    # with open(sys.argv[2]) as file:
    #     reader3 = csv.DictReader(file)
    #     print(reader3.fieldnames)

    with open(sys.argv[2]) as file:
        reader4 = file.read()

    # Find longest match of each STR in DNA sequence

    # print(reader4[2:6])

    # print(len(reader4))

    # print(int(len(reader4) / 4))

    # AGATC
    agatcCount = longest_match(reader4, "AGATC")
    # TTTTTTCT
    ttttttctCount = longest_match(reader4, "TTTTTTCT")
    # AATG
    aatgCount = longest_match(reader4, "AATG")
    # TCTAG
    tctagCount = longest_match(reader4, "TCTAG")
    # GATA
    gataCount = longest_match(reader4, "GATA")
    # TATC
    tatcCount = longest_match(reader4, "TATC")
    # GAAA
    gaaaCount = longest_match(reader4, "GAAA")
    # TCTG
    tctgCount = longest_match(reader4, "TCTG")

    # len(s) and s[i:j] int(x)

    # print(longest_match(reader4, "AGATC"))

    # print(f"AGATC: {agatcCount}")
    # print(f"AATG: {aatgCount}")
    # print(f"TATC: {tatcCount}\n")

    # print(f"AGATC: {agatcCount}")
    # print(f"TTTTTTCT: {ttttttctCount}")
    # print(f"AATG: {aatgCount}")
    # print(f"TCTAG: {tctagCount}")
    # print(f"GATA: {gataCount}")
    # print(f"TATC: {tatcCount}")
    # print(f"GAAA: {gaaaCount}")
    # print(f"TCTG: {tctgCount}\n")

    # save STR counts in a list or dictionary

    dictionary = dict(AGATC=agatcCount,
                      TTTTTTCT=ttttttctCount,
                      AATG=aatgCount,
                      TCTAG=tctagCount,
                      GATA=gataCount,
                      TATC=tatcCount,
                      GAAA=gaaaCount,
                      TCTG=tctgCount
                      )

    # print(dictionary['TCTG'])

    # for row in rows:
    #     print(rows[0]["name"])

    # Check database for matching profiles

    names = list(rows[0].keys())[1:]

    match = None

    # for each row in the data, check if STR count matches, print out the persons name
    # to confirm a match youll need to check every column other than the first column
    for row in rows:
        if all(int(row[name]) == dictionary[name] for name in names):
            match = row["name"]
            break
    if match:
        print(match)
    else:
        print("No Match")

    # print(rows[0])
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
