import csv
import sys


def main():

    # TODO: Check for command-line usage
    l = len(sys.argv)
    if (l < 3 or l > 3):
        print("Usage python dna.py data.csv sequence.txt")
        sys.exit()
    # TODO: Read database file into a variable
    db = sys.argv[1]

    with open(db) as d:
        r = csv.DictReader(d)
        dnaBase = []
        for p in r:
            if (db == "databases/large.csv"):
                dict = {}
                strc = {}
                p["AGATC"] = int(p["AGATC"])
                strc["AGATC"] = p["AGATC"]
                p["TTTTTTCT"] = int(p["TTTTTTCT"])
                strc["TTTTTTCT"] = p["TTTTTTCT"]
                p["AATG"] = int(p["AATG"])
                strc["AATG"] = p["AATG"]
                p["TCTAG"] = int(p["TCTAG"])
                strc["TCTAG"] = p["TCTAG"]
                p["GATA"] = int(p["GATA"])
                strc["GATA"] = p["GATA"]
                p["TATC"] = int(p["TATC"])
                strc["TATC"] = p["TATC"]
                p["GAAA"] = int(p["GAAA"])
                strc["GAAA"] = p["GAAA"]
                p["TCTG"] = int(p["TCTG"])
                strc["TCTG"] = p["TCTG"]
                dict[p["name"]] = strc
                dnaBase.append(dict)
            elif (db == "databases/small.csv"):
                dict = {}
                strc = {}
                p["AGATC"] = int(p["AGATC"])
                strc["AGATC"] = p["AGATC"]
                p["AATG"] = int(p["AATG"])
                strc["AATG"] = p["AATG"]
                p["TATC"] = int(p["TATC"])
                strc["TATC"] = p["TATC"]
                dict[p["name"]] = strc
                dnaBase.append(dict)
    # TODO: Read DNA sequence file into a variable
    seq = sys.argv[2]
    with open(seq, 'r') as s:
        seq = s.read()
    # TODO: Find longest match of each STR in DNA sequence
    seqstrc = {}
    for keys, values in dnaBase[0].items():
        for key, value in values.items():
            seqstrc[key] = longest_match(seq, key)
    # TODO: Check database for matching profiles
    # creating a variable to see the no match case
    f = False
    if (db == "databases/large.csv"):
        for i in range(23):
            for key, values in dnaBase[i].items():
                if (dnaBase[i][key] == seqstrc):
                    print(f"{key}")
                    f = True
                elif (i == 22 and not(f)):
                    print("No match")
    elif (db == "databases/small.csv"):
        for i in range(3):
            for key, values in dnaBase[i].items():
                if (dnaBase[i][key] == seqstrc):
                    print(f"{key}")
                    f = True
                elif (i == 2 and not(f)):
                    print("No match")
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
