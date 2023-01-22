# import library
from cs50 import get_int

# prompts user for height, if height is outside range program re-prompts
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

# for loop for the vertical range of pyramid
for number in range(height):

    # for loop for leading spaces
    space = 1
    for space in range(height - number - 1):
        print(" ", end="")

    # for loop for ## in first pyramid
    row1 = 1
    for row1 in range(number+1):
        print("#", end="")
    print("  ", end="")

    # for loop for ## in second pyramid
    row2 = 1
    for row2 in range(number+1):
        print("#", end="")
    print("")

