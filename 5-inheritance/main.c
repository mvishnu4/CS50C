#include "cs50.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct person
//struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int generations = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele(void);

int main(int argc, const char * argv[])
{
    srand(floor(time(0)));
    
    person *p = create_family(generations);
    print_family(p, 0);
    free_family(p);
    printf("freed\n");
}

person *create_family(int generations)
{
    //Allocate memory for new person
    person *p = malloc(sizeof(person));

    if (generations > 1)
    {
        //recursively create blood type histories for parents
        //while (generations > 0)
        //{
            person *parents0 = create_family(generations - 1);
            person *parents1 = create_family(generations - 1);
            
            p -> parents[0] = parents0;//child -> parents[0];
            p -> parents[1] = parents1;//child -> parents[0];
            
            p -> alleles[0] = p -> parents[0] -> alleles[rand()%2];
            p -> alleles[1] = p -> parents[1] -> alleles[rand()%2];
        //}
    }
    else
    {
        //set parent pointer to NULL
        p ->parents[0]= NULL;
        p ->parents[1]= NULL;
        //grandparen1 = NULL;
        //grandparen2 = NULL;
        //paren1 = NULL;
        //paren2 = NULL;
        //randoonly assign alleles
        p -> alleles[0] = random_allele();
        p -> alleles[1] = random_allele();
    }
    //return newly created person
    return p;
}

void print_family(person *p, int generation)
{
    if (p == NULL)
    {
        return;
    }
    //print intendation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf("   ");
    }
    
    //print person
    printf(" Generation %i, blood type %c%c\n", generation, p -> alleles[0], p -> alleles[1]);
    
    print_family(p -> parents[0], generation + 1);
    print_family(p -> parents[1], generation + 1);
}

void free_family(person *p)
{
    //handle base cases
    if (p==NULL)
    {
        return;
    }
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    //free child
    free(p);
}

char random_allele(void)
{
    int r = random() % 3;
    if (r == 0)
    {
        return  'A';
    }
    else if (r == 1)
    {
        return  'B';
    }
    else
    {
        return 'O';
    }
}
/*
 person *paren1 = malloc(sizeof(person));
 person *paren2 = malloc(sizeof(person));
 person *grandparen1 = malloc(sizeof(person));
 person *grandparen2 = malloc(sizeof(person));
 person *generationlist = NULL;
 
 child = paren1;
    paren1 = grandparen1;
    paren2 = grandparen2;
    generations -= 1;
}

grandparen1 -> alleles[0] = random_allele();
grandparen1 -> alleles[1] = random_allele();
grandparen2 -> alleles[0] = random_allele();
grandparen2 -> alleles[1] = random_allele();
//randomly assign child alles based on parents
paren1 -> alleles[0] = grandparen1 -> alleles[rand()%2];
paren1 -> alleles[1] = grandparen2 -> alleles[rand()%2];
paren2 -> alleles[0] = grandparen1 -> alleles[rand()%2];
paren2 -> alleles[1] = grandparen2 -> alleles[rand()%2];
child -> alleles[0] = paren1 -> alleles[rand()%2];
child -> alleles[1] = paren2 -> alleles[rand()%2];

child -> parents[0] = generationlist;
child -> parents[1] = generationlist;
paren1 -> parents[0] = generationlist;
paren1 -> parents[1] = generationlist;
paren2 -> parents[0] = generationlist;
paren2 -> parents[1] = generationlist;*/
