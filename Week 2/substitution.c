#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])       //function to accept argument input when program runs
{
    char key[26];
    int alpha = 0, dup = 0;
    if (argc == 2)
    {
        strcat(key, argv[1]);               //startup argument into a string
        for (int c = 0; c < strlen(key); c++)            //loop to check characters
        {
            if (isalpha(key[c]))         //check characters are alpha
            {
                alpha++;
            }
            for (int d = 0; d < strlen(key); d++)  //check characters are not duplicated
            {
                if (key[d] == key[c])
                {
                    dup++;
                }
            }
        }
    }
    else
    {
        printf("invalid\n");                            //if no argument is entered when running program
        return (1);
    }
    if (strlen(key) == 26 && alpha == 26 && dup == 26)      //must have at least one argument entered and string must be 26 characters
    {
        string plain = get_string("plaintext: ");       //for entry on the phrase to be encoded
        printf("ciphertext: ");
        for (int j = 0; j < strlen(plain); j++)        // loop to go through 'plain' and convert to letters from key
            if isupper(plain[j])                       // check if letter is upper, lower or other
            {
                printf("%c", toupper(key[((int)plain[j]) - 65])); // prints char from the index of KEY = the ascii minus 65
            }
            else if islower(plain[j])
            {
                printf("%c", tolower(key[((int)plain[j]) - 97])); // prints char from the index of KEY = the ascii minus 97
            }
            else
            {
                printf("%c", plain[j]);
            }
        printf("\n");                                    // CR after word is completed
    }
    else
    {
        printf("invalid\n");                            //if no argument is entered when running program
        return (1);


    }
}


