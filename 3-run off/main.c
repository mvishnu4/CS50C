#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    char* name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;
int num = 3;
// Function prototypes
bool vote(int voter, int rank, char* name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, char* argv[])
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
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    int voter_count;
    printf("number of voters");
    scanf("%i",&voter_count);
    
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
            char name[7];
            printf("Rank%i: ",j+1);
            scanf("%s",name);
            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    printf("tabulated\n");
    for (int i=0; i<voter_count; i++)
    {
        for (int j=0; j<candidate_count; j++)
        {
            printf("%i",preferences[i][j]);
        }
        printf("\n");
    }
    
    
    // Keep holding runoffs until winner exists
    while (true)
    {printf("**tab**");
        // Calculate votes given remaining candidates
        tabulate();
        
        // Check if election has been won
        bool won = print_winner();
        if (won == true)
        {
            printf("**win**");
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
                    printf("%s %i\n", candidates[i].name,candidates[i].votes);
                }
            }
            printf("**tie**");
            break;
        }

        eliminate(min);
        // Eliminate anyone with minimum number of votes

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
            printf("%s %i",candidates[i].name,candidates[i].votes);
        }
        break;
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, char* name)
{
    int i = voter;
    int j = rank;
    for (int k=0; k<candidate_count; k++)
    {
        if(strcmp(candidates[k].name,name)==0)
        {
            preferences[i][j] = k;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int k=0; k<candidate_count+num; k++)
    {
        for(int j=0; j<candidate_count; j++)
        {
            if(preferences[k][0]==j)
            {
               
                candidates[j].votes+=1;
                //printf("%s %i ",candidates[j].name,candidates[j].votes);
                break;
            }
        }
    }
   printf("/*");
   for(int j=0; j<candidate_count; j++)
   {
       printf("%s %i ",candidates[j].name,candidates[j].votes);
    }printf("/ \n");

   for(int p=0; p<candidate_count-1;p++)
   {
       printf("r:%i\n",p+1);
       if(!print_winner())
       {
           printf("1min:%i\n",find_min());
           if(!is_tie(find_min()))
           {
               eliminate(find_min());
               for (int k=0; k<candidate_count+num; k++)
               {
                   for (int j=0; j<candidate_count; j++)
                   {
                       if(preferences[k][p]==-1&&preferences[k][p+1]==j)
                       {
                           candidates[j].votes+=1;
                           printf("%s %i",candidates[j].name,candidates[j].votes);
                           break;
                       }
                   }
               }
           }
           else
           {
               printf("2min:%i\n",find_min());
               
               for (int k=0; k<candidate_count+num; k++)
               {
                   for (int j=0; j<candidate_count; j++)
                   {
                       if(preferences[k][p+1]==j)
                       {
                           if(candidates[j].votes!=0)
                           {
                               candidates[j].votes+=1;
                               printf("%s %i",candidates[j].name,candidates[j].votes);
                               break;
                           }
                       }
                   }
               }
           }
       }
       else
       {
           break;
       }
       
       /*else
       {
           break;
       }*/
       
       
       printf("\n/*");
       for(int j=0; j<candidate_count; j++)
       {
           if(candidates[j].eliminated != true)
           {
               printf("%s %i",candidates[j].name,candidates[j].votes);
           }
       }
       printf("/\n");
   }
   /* if(!print_winner())
    {
        printf("1min:%i\n",find_min());
        if(!is_tie(find_min()))
        {
            eliminate(find_min());
            for (int k=0; k<candidate_count+num; k++)
            {
                for (int j=0; j<candidate_count; j++)
                {
                    if(preferences[k][1]==-1&&preferences[k][2]==j)
                    {
                        candidates[j].votes+=1;
                        printf("%s %i",candidates[j].name,candidates[j].votes);
                        break;
                    }
                }
            }
        }
        else
        {
            printf("2min:%i\n",find_min());
            for (int k=0; k<candidate_count+num; k++)
            {
                for (int j=0; j<candidate_count; j++)
                {
                        if(preferences[k][2]==j)
                        {
                            candidates[j].votes+=1;
                            printf("%s %i",candidates[j].name,candidates[j].votes);
                            break;
                        }
                }
            }
        }
    }
        printf("\n/");
        for(int j=0; j<candidate_count; j++)
        {
            printf("%s %i",candidates[j].name,candidates[j].votes);
        }
        printf("/\n");*/
    
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int mk = 0;
    voter_count = candidate_count+num;
    for(int i=0; i<candidate_count; i++)
    {
        if(candidates[i].votes>mk)
        {
            mk = candidates[i].votes;
        }
    }
    printf("mk:%i\n",mk);
    for(int i=0; i<candidate_count; i++)
    {
        if(candidates[i].votes==mk)
        {
            if(mk>voter_count/2)
            {
                if(!is_tie(mk))
                {
                   // printf("####");
                    //printf("won\n");
                    printf("%s %i\n",candidates[i].name,candidates[i].votes);
                    return true;
                }
            }
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min=candidates[0].votes;
    for (int j=0; j<candidate_count; j++)
    {
        if(j>=0&&candidates[j].eliminated!=true)
        {
            if(candidates[j].votes<min)
            {
                min = candidates[j].votes;
            }
        }
    }
    
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for(int i=0; i<candidate_count; i++)
    {
        for(int n=1; n<candidate_count; n++)
        {
            if(i+n<candidate_count)
            {
                if((candidates[i].votes==min)&&(candidates[i+n].votes==min))
                {
                    //printf("\ntie %i%i\n",i,i+n);
                    return true;
                    break;
                }
            }
        }
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
        for(int e=0; e<candidate_count; e++)
        {
            if(candidates[e].votes==min)
            {
                printf("%s $\n",candidates[e].name);
                candidates[e].eliminated = true;
                candidates[e].votes = 0;
                printf("e:%i\n",e);
                for(int k=0; k<candidate_count+num;k++)
                {
                        if(preferences[k][0]==e)
                        {
                            preferences[k][0]=-1;
                        }
                }
            }
        }
    return;
}

/*
 2* abc
 3* bac
 2* cab
 2* cba
 */
 
/*number of voters4
 Rank1: a Rank2: b Rank3: c
 Rank1: a Rank2: b Rank3: c
 Rank1: b Rank2: a Rank3: c
 Rank1: b Rank2: a Rank3: c
 tabulated 012 012 102 102
 **tab/a 2 b 2 c 0 /
 r:1 mk:2
 1min:0
 c $ e:2
 /a 2b 2/
 r:2 mk:2
 1min:2 2min:2
 /a 2b 2/ mk:2
 a 2
 b 2
 **tie**
 */

/*
 number of voters6
 Rank1: a Rank2: b Rank3: c
 Rank1: c Rank2: a Rank3: b
 Rank1: b Rank2: c Rank3: a
 Rank1: a Rank2: b Rank3: c
 Rank1: c Rank2: a Rank3: b
 Rank1: a Rank2: b Rank3: c
 tabulated 012 201 120 012 201 012
 **tab/a 3 b 1 c 2 /
 r:1 mk:3
 1min:1
 b $ e:1
 c 3
 /a 3c 3/
 r:2 mk:3
 1min:3 2min:3
 c 4a 4c 5c 6
 /a 4c 6/
 mk:6
 c 6 **win**
 */
