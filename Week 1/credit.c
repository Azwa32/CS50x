#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Requests card number
    long cc;
    do
    {
        cc = get_long("Number: ");
    }
    while (cc < 0); //card # is greater than 0

    int loc1, loc2, loc3, loc4, loc5, loc6, loc7, loc8;
    loc1 = ((cc % 100) / 10) * 2;
    loc2 = ((cc % 10000) / 1000) * 2;
    loc3 = ((cc % 1000000) / 100000) * 2;
    loc4 = ((cc % 100000000) / 10000000) * 2;
    loc5 = ((cc % 10000000000) / 1000000000) * 2;
    loc6 = ((cc % 1000000000000) / 100000000000) * 2;
    loc7 = ((cc % 100000000000000) / 10000000000000) * 2;
    loc8 = ((cc % 10000000000000000) / 1000000000000000) * 2;

    loc1 = (loc1 % 100) / 10 + (loc1 % 10);
    loc2 = (loc2 % 100) / 10 + (loc2 % 10);
    loc3 = (loc3 % 100) / 10 + (loc3 % 10);
    loc4 = (loc4 % 100) / 10 + (loc4 % 10);
    loc5 = (loc5 % 100) / 10 + (loc5 % 10);
    loc6 = (loc6 % 100) / 10 + (loc6 % 10);
    loc7 = (loc7 % 100) / 10 + (loc7 % 10);
    loc8 = (loc8 % 100) / 10 + (loc8 % 10);

    int loc9, loc10, loc11, loc12, loc13, loc14, loc15, loc16;
    loc9 = (cc % 10);
    loc10 = ((cc % 1000) / 100);
    loc11 = ((cc % 100000) / 10000);
    loc12 = ((cc % 10000000) / 1000000);
    loc13 = ((cc % 1000000000) / 100000000);
    loc14 = ((cc % 100000000000) / 10000000000);
    loc15 = ((cc % 10000000000000) / 1000000000000);
    loc16 = ((cc % 1000000000000000) / 100000000000000);

    loc9 = (loc9 % 100) / 10 + (loc9 % 10);
    loc10 = (loc10 % 100) / 10 + (loc10 % 10);
    loc11 = (loc11 % 100) / 10 + (loc11 % 10);
    loc12 = (loc12 % 100) / 10 + (loc12 % 10);
    loc13 = (loc13 % 100) / 10 + (loc13 % 10);
    loc14 = (loc14 % 100) / 10 + (loc14 % 10);
    loc15 = (loc15 % 100) / 10 + (loc15 % 10);
    loc16 = (loc16 % 100) / 10 + (loc16 % 10);

    const int even = loc1 + loc2 + loc3 + loc4 + loc5 + loc6 + loc7 + loc8;
    const int odd = loc9 + loc10 + loc11 + loc12 + loc13 + loc14 + loc15 + loc16;
    const int check = even + odd;
    int length = 0;

    //to get length of cc string
    while (cc > 0)
    {
        cc = (cc / 10);
        length = (length + 1);
    }

    //check for invalid card
    if ((check % 10) == 0)
    {
        //for Amex
        if (length == 15 && loc16 == 3 && (loc7 == 8 || loc7 == 5))
        {
            printf("AMEX\n");
        }
        //for Visa a
        else if ((length == 13 && loc15 == 4) || (length == 16 && loc8 == 8))
        {
            printf("VISA\n");
        }
        else if (length == 16)
        {
            //for Visa b
            if (loc8 == 8)
            {
                printf("VISA\n");
            }
            //for Mastercard
            else if (loc8 == 1 && (loc16 == 1 || loc16 == 2 || loc16 == 3 || loc16 == 4 || loc16 == 5))
            {
                printf("MASTERCARD\n");
            }
            //no match
            else
            {
                printf("INVALID\n");
            }
        }
        //no match
        else
        {
            printf("INVALID\n");
        }
    }
    //no match
    else
    {
        printf("INVALID\n");
    }


}
