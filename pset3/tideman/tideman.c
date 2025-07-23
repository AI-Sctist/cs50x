#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];
int visited[MAX]; // Array to mark the visited vertices
int mark;         // visited[i] == mark means vertex i has been visited

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

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
int diff(int i);
bool can_reach(int cur, int targ);

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

    // Initialize graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        // Keep track of the pair that had the maximum point difference
        int mx = i;

        // Find the index of the pair that has maximum point difference
        for (int j = i + 1; j < pair_count; j++)
        {
            if (diff(j) > diff(mx))
            {
                mx = j;
            }
        }

        // Swap two pairs
        pair temp = pairs[i];
        pairs[i] = pairs[mx];
        pairs[mx] = temp;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Update to overwrite the old visited[]
        mark++;

        /* When we lock in winner over loser, a directed path from winner to loser
        formed, to ensure there's no cycle, there must be no existing path from
        loser to winner before. */
        if (!can_reach(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election (the root of a graph)
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            // If j locked in i, i is not the root
            if (locked[j][i])
            {
                is_winner = false;
            }
        }

        if (is_winner)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}

// Calculate the point difference between two candidates in a given pair
int diff(int i)
{
    int win = pairs[i].winner;
    int lose = pairs[i].loser;
    return preferences[win][lose] - preferences[lose][win];
}

// Check if vertex cur can reach vertex targ
bool can_reach(int cur, int targ)
{
    if (cur == targ)
    {
        return true;
    }
    else
    {
        visited[cur] = mark;
    }

    for (int v = 0; v < candidate_count; v++)
    {
        // If there exists a directed path from cur to v
        if (locked[cur][v] && visited[v] != mark)
        {
            bool ok = can_reach(v, targ);
            if (ok)
            {
                return true;
            }
        }
    }

    // Cannot reach after trying all the paths
    return false;
}
