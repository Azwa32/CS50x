#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 Wins! \n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 Wins! \n");
    }
    else
    {
        printf("Tie! \n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string

    //run a for loop over the word
    //is letter caps?
    //true
    // POINTS[i] = letter int - 65
    //false
    // POINTS[i] = letter int - 97
    string w = word;
    int p = 0;
    for (int i = 0, n = strlen(w); i < n; i++)
    {
        if (isupper(w[i]))
        {
            p = p + POINTS[(((w[(int)i]) - 65))];
        }
        else if (islower(w[i]))
        {
            p = p + POINTS[(((w[(int)i]) - 97))];
        }
    }
    printf("%i\n", p);
    return (p);

}
