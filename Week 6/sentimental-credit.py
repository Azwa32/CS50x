from cs50 import get_string

# Requests card number
while True:
    ccString = get_string("Number: ")
    if len(ccString) == 0:
        break

    cc = int(ccString)
    length = len(ccString)

    # even numbers
    # get modulus
    loc1 = int((cc % 100) / 10) * 2
    loc2 = int((cc % 10000) / 1000) * 2
    loc3 = int((cc % 1000000) / 100000) * 2
    loc4 = int((cc % 100000000) / 10000000) * 2
    loc5 = int((cc % 10000000000) / 1000000000) * 2
    loc6 = int((cc % 1000000000000) / 100000000000) * 2
    loc7 = int((cc % 100000000000000) / 10000000000000) * 2
    loc8 = int((cc % 10000000000000000) / 1000000000000000) * 2

    # get sum of individual int
    loc1 = int((loc1 % 100) / 10) + (loc1 % 10)
    loc2 = int((loc2 % 100) / 10) + (loc2 % 10)
    loc3 = int((loc3 % 100) / 10) + (loc3 % 10)
    loc4 = int((loc4 % 100) / 10) + (loc4 % 10)
    loc5 = int((loc5 % 100) / 10) + (loc5 % 10)
    loc6 = int((loc6 % 100) / 10) + (loc6 % 10)
    loc7 = int((loc7 % 100) / 10) + (loc7 % 10)
    loc8 = int((loc8 % 100) / 10) + (loc8 % 10)

    # odd numbers
    # get modulus
    loc9 = int(cc % 10)
    loc10 = int((cc % 1000) / 100)
    loc11 = int((cc % 100000) / 10000)
    loc12 = int((cc % 10000000) / 1000000)
    loc13 = int((cc % 1000000000) / 100000000)
    loc14 = int((cc % 100000000000) / 10000000000)
    loc15 = int((cc % 10000000000000) / 1000000000000)
    loc16 = int((cc % 1000000000000000) / 100000000000000)

    # get sum of individual int
    loc9 = int((loc9 % 100) / 10) + (loc9 % 10)
    loc10 = int((loc10 % 100) / 10) + (loc10 % 10)
    loc11 = int((loc11 % 100) / 10) + (loc11 % 10)
    loc12 = int((loc12 % 100) / 10) + (loc12 % 10)
    loc13 = int((loc13 % 100) / 10) + (loc13 % 10)
    loc14 = int((loc14 % 100) / 10) + (loc14 % 10)
    loc15 = int((loc15 % 100) / 10) + (loc15 % 10)
    loc16 = int((loc16 % 100) / 10) + (loc16 % 10)

    even = loc1 + loc2 + loc3 + loc4 + loc5 + loc6 + loc7 + loc8
    odd = loc9 + loc10 + loc11 + loc12 + loc13 + loc14 + loc15 + loc16
    check = even + odd

    # check for invalid card
    if ((check % 10) == 0):

        # for Amex

        if (length == 15 and loc16 == 3) and (loc7 == 8 or loc7 == 5):
            print("AMEX")
            break

        # for Visa a
        elif ((length == 13 and loc15 == 4) or (length == 16 and loc8 == 8)):
            print("VISA")
            break
        elif (length == 16):

            # for Visa b
            if (loc8 == 8):
                print("VISA")
                break

            # for Mastercard

            elif (loc8 == 1 & (loc16 == 1 or loc16 == 2 or loc16 == 3 or loc16 == 4 or loc16 == 5)):
                print("MASTERCARD")
                break

            # no match
            else:
                print("INVALID")
                break

        # no match
        else:
            print("INVALID")
            break

    # no match
    else:
        print("INVALID")
        break
