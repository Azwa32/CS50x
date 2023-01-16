from cs50 import get_string

# index = 0.0588 * L - 0.296 * S - 15.8
# L = number of letters per 100 words
# S = number of sentences per 100 words

letters = 0
words = 1
sentences = 0
L = 0
S = 0
grade = 0

# Ask for text
string = get_string("Text:")
length = len(string)

for i in range(length):
    # find the amount of letters
    if ((string[i] >= 'A' and string[i] <= 'Z') or (string[i] >= 'a' and string[i] <= 'z')):
        letters += 1

    # find the amount of words
    elif (string[i] == ' '):
        words += 1

    # find the amount of sentences
    elif (string[i] == '.' or string[i] == '!' or string[i] == '?'):
        sentences += 1

# find the average letters per 100 words
L = (letters / words * 100)

# find the average sentences per 100 words
S = (sentences / words * 100)

# run Colman-Liau calc
grade = 0.0588 * L - 0.296 * S - 15.8

# if grade is less than gradee 1
if (grade < 1):
    print("Before Grade 1")

# if grade is 16 or above
elif (grade >= 16):
    print("Grade 16+")

else:
    print("Grade ", round(grade))