#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    //pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)  // initialise loop
    {
        if (strcmp(candidates[i], name) == 0)  // if the candidates name has been previously indexed
        {
            ranks[rank] = i;                   // in the ranks array at the index of 'rank' (is j from the loop above) put the candidates index #
            return true;                       // event successfully recorded
        }
    }
    return false;                              // event was not successfull recorded
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int r = 0; r < candidate_count; r++)    // loop for rows
    {
        for (int c = r + 1; c < candidate_count; c++)   //loop for cell, column by column
        {
            preferences[ranks[r]][ranks[c]]++;   // adds 1 to the required array cells
        }
    }
    //debug output
    //printf("%d %d %d %d\n", preferences[0][0], preferences[0][1], preferences[0][2], preferences[0][3]);
    //printf("%d %d %d %d\n", preferences[1][0], preferences[1][1], preferences[1][2], preferences[1][3]);
    //printf("%d %d %d %d\n", preferences[2][0], preferences[2][1], preferences[2][2], preferences[2][3]);
    //printf("%d %d %d %d\n", preferences[3][0], preferences[3][1], preferences[3][2], preferences[3][3]);

    return;

}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;                               //initialise the pair count
    for (int r1 = 0; r1 < candidate_count-1; r1++)  //create loop for scanning row. -1 as argc candidate count starts at -1
    {
        for (int c1 = r1 + 1; c1 < candidate_count; c1++)  // create loop for scanning column,
        {
            if (preferences[r1][c1] > preferences[c1][r1]) //if candidate from top row is winner
            {
                 pairs[pair_count].winner = r1;   //winner is candidate from top row
                 pairs[pair_count].loser = c1;    //loser is candidate from side row
                 pair_count++;                    //increase paircount by one
            }
            else if (preferences[c1][r1] > preferences[r1][c1])   // if candidate from side column is winner
            {
                pairs[pair_count].winner = c1;   //winner is candidate from side row
                pairs[pair_count].loser = r1;    //loser is candidate from top row
                pair_count++;                    //increase paircount by one
            }
        }
    }
    //to check output
    //for (int i = 0; i < pair_count; i++)
    //{
    //    printf("%d | %d\n", pairs[i].winner, pairs[i].loser);
    //}
    //printf("\n");
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    pair temp;
    int sort = 0;
    for (int i = 1; i < pair_count; i++) // go through pairs winner indexes
	{
        int j = i - 1;   // index the position after the currently scanned possition
        temp = pairs[j];  // park the data at current position
		if (preferences[pairs[i].winner][pairs[i].loser] > preferences[pairs[j].winner][pairs[j].loser])  // which is higher the column or the row version
		{
			pairs[j] = pairs[i];  // + VV  swap positions
            pairs[i] = temp;
            sort++;               // add to the sort count
		}
    }
    if (sort > 0)                   //if sort function has been used
    {
        sort_pairs();             // run function recursively
    }
    else
    {
        //for (int i = 0; i < pair_count; i++ )    //debug print
        //{
        //    printf("w %d | l %d | v %d | i %d\n", pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser], i);
        //}
        //printf("\n");
        return;                     // return to main prog
    }
}

bool looped(int winner, int loser)    // recursive function for lock_pairs
{
    if (loser == winner)  // to prevent pairs from creating a cycle
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])  // check if candidate has already won over anyone, if so
        {
            if (looped(winner, i))   // recursive function to check if the winner has won against the same candidate
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int r = 0; r < pair_count; r++)  //create loop for scanning row
    {
        if (!looped(pairs[r].winner, pairs[r].loser))   //if 'looped' function returns false
        {
            locked[pairs[r].winner][pairs[r].loser] = true;   // set cell in array to true
        }
    }

    //does the loser win in any pairs that are already locked, if not then proceed
    //debug print
    for (int r = 0; r < pair_count; r++)
    {
        for (int c = 0; c < pair_count; c++)
        {
            printf("%d ", locked[r][c]);
        }
        printf("\n");
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // looking for the candidate with no 'true' values in their column, thus has no one pointing at them.
    for (int c = 0; c < candidate_count; c++)
    {
        bool winner = true;
        for (int r = 0; r < candidate_count; r++)
        {
            if (locked[r][c] == true)
            {
                winner = false;
            }
        }
        if (winner == true)
        {
            printf("%s\n", candidates[c]);
        }
    }
    return;
}