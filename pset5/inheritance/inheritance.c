// Simulate genetic inheritance of blood type
#define _DEFAULT_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

// Branch and bound: Check if a family is successfully create, early stop creating new
// member if some branches are failed, but still keep the paths to free.
bool SUCCESSFULL = true;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srandom(time(0));

    if (GENERATIONS == 0)
    {
        printf("No generation for creating.\n");
        return 1;
    }

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    if (SUCCESSFULL)
    {
        print_family(p, 0);
    }
    else
    {
        printf("Create failed!\n");
    }

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    if (!SUCCESSFULL)
    {
        return NULL;
    }

    // TODO: Allocate memory for new person
    person *member = malloc(sizeof(person));
    if (member == NULL)
    {
        SUCCESSFULL = false;
        return NULL;
    }

    // If there are still generations left to create
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);
        if (parent0 == NULL || parent1 == NULL)
        {
            SUCCESSFULL = false;
        }

        // TODO: Set parent pointers for current person
        member->parents[0] = parent0;
        member->parents[1] = parent1;

        // TODO: Randomly assign current person's alleles based on the alleles of their parents
        if (SUCCESSFULL)
        {
            member->alleles[0] = parent0->alleles[rand() % 2];
            member->alleles[1] = parent1->alleles[rand() % 2];
        }
    }

    // If there are no generations left to create
    else
    {
        // TODO: Set parent pointers to NULL
        member->parents[0] = NULL;
        member->parents[1] = NULL;

        // TODO: Randomly assign alleles
        member->alleles[0] = random_allele();
        member->alleles[1] = random_allele();
    }

    // TODO: Return newly created person
    return member;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case
    if (p == NULL)
    {
        return;
    }

    // TODO: Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // TODO: Free child
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0],
               p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0],
               p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0],
               p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = random() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
