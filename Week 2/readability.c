#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// index = 0.0588 * L - 0.296 * S - 15.8
// L = number of letters per 100 words
// S = number of sentences per 100 words


int main(void)
{
    // Ask for text
    // find the amount of letters
    // find the amount of words
    // find the amount of sentences
    // find the average letters per 100 words
    // find the average sentences per 100 words
    // run Colman-Liau calc

    string s = get_string("Text: ");
    float letters = 0;
    float words = 1;
    float sentences = 0;
    float L = 0;
    float S = 0;
    float grade = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // find the amount of letters
        if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
        {
            letters += 1;
        }
        // find the amount of words
        else if (s[i] == 32)
        {
            words += 1;
        }
        // find the amount of sentences
        else if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences += 1;
        }
    }
    // find the average letters per 100 words
    L = (letters / words * 100);
    // find the average sentences per 100 words
    S = (sentences / words * 100);
    // run Colman-Liau calc
    grade = 0.0588 * L - 0.296 * S - 15.8;
    // if grade is less than grade 1
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    // if grade is 16 or above
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(grade));  //takes grade float, rounds to 00, then changes to int
    }
}