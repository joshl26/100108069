// Harvard CS50X Problem Set Submission
// Problem Set 3 - Runoff
// By Joshua Lehman - May 15, 2024

#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    // Set the default values for each candidate struct in the candidates up to canidate_count
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");

    // Check voter count, if larger than MAX_VOTERS return 3, end program.
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid, return 4, end program.
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    // If name matches a valid candidate,
    // Assume no two candidates have the same name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Update the global preferences array for that voter

            preferences[voter][rank] = i;

            return true;
        }
    }

    // If preference is recorded the function should return true else return false. i.e. name is not
    // valid candidate name
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{

    // Update the number of votes each candidate has at this stage in the runoff.
    // At each stage in the run off, every voter effectively votes for their top
    // preferred candidate who has not already been eliminated.

    // candidates[MAX_CANDIDATES]

    for (int i = 0; i < voter_count; i++)
    {
        // candidates[preferences[i][0]].votes += 1;
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                // if preference selection = candidate index number increment vote by 1
                candidates[preferences[i][j]].votes += 1;
                break;
            }
        }
    }

    // , where i is the candidate index and j is the voter index

    // candidate_count

    // voter_count

    // preferences[i][j]

    // preferences[i][0] - first choice
    // preferences[i][1] - second choice
    // preferences[i][candidate_count-1] - last choice (will be removed each round)

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{

    int votes_to_win = voter_count / 2;

    // If any candidate has more than half the vote, return true
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > votes_to_win)
        {
            printf("The winner is: %s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int votes = voter_count;

    // Return the minimum vote total for any candidate still in the race
    for (int i = 0; i < candidate_count; i++)
    {

        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes < votes)
            {
                votes = candidates[i].votes;
            }
        }
    }
    return votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {

        if (candidates[i].votes != min && candidates[i].eliminated == false)
        {
            return false;
        }
    }

    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{

    int candidates_left = candidate_count;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            candidates_left += 1;
        }
    }

    // Eliminate the candidate, or candidates who have the min number of votes
    for (int i = 0; i < candidates_left; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }

    return;
}
