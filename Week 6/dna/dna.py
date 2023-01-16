import csv
import sys


def main():

    # TODO: Check for command-line usage\
    # use sys.argv for getting the command line arguments eg csv & dna string
    csv_arg = sys.argv[1]
    text_arg = sys.argv[2]

    # TODO: Read database file into a variable
    # open file using 'open(filename)'
    csv_file = open(csv_arg)

    # use reader / DictReader for reading files, read into a 2d array using 'filename.read'
    database = []
    with csv_file as file:
        database = list(csv.reader(file))

    # TODO: Read DNA sequence file into a variable
    # open file using 'open(filename)'
    text_file = open(text_arg)

    # read into string using 'filename.read'
    string = text_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    # create var for largest occourance of STR
    STR_QTY = len(database[0])-1
    DNA = [0] * (STR_QTY)
    # for loop, count number of matches for each DNA type
    # DNA[i] = string.count('AGATC')
    for i in range(1, STR_QTY+1):
        DNA[i-1] = longest_match(string, database[0][i])

    # TODO: Check database for matching profiles
    # check each type of DNA against each person

    # initialise match_name var
    match_name = 'No match'

    # match STR qty's of specimen to members of database
    for person in range(1, len(database)):
        STR_Match = 0
        name = database[person][0]
        for i in range(1, len(database[person])):
            if int(database[person][i]) == DNA[i-1]:
                STR_Match += 1
                if int(STR_Match) == int(STR_QTY):
                    match_name = database[person][0]

    # if so print name
    # if not print 'no match'
    print(match_name)

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
