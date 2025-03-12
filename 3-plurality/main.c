#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define  MAX 9

typedef struct
{
    const char* name;
    int votes;
}candidate;

candidate candidates[MAX];

int candidate_count;
int f=0;
bool vote(char* name);
void print_winner(void);

int main(int argc, const char * argv[])
{
   if(argc<2)
   {
       printf("Useage: plurality[camndidate]\n");
       return 1;
   }
    
    candidate_count = argc-1;

    if(candidate_count>MAX)
    {
        printf("max number exceded");
        return 2;
    }
    
    for (int i=0; i<candidate_count; i++)
    {
        candidates[i].name = argv[i+1];
        candidates[i].votes = 0;
    }
    
    int votercount;
    printf("no of voters: ");
    scanf("%i",&votercount);

    for (int i=0; i<votercount;i++)
    {
        char name[7];
        printf("vote:");
        scanf("%s",name);
        
        if(!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }
    print_winner();
}

bool vote(char* name)
{
    for (int j=0; j<candidate_count; j++)
    {
        if(strcmp(candidates[j].name,name)==0)
        {
            candidates[j].votes+=1;
            return true;
        }
    }
    return false;
}
 

void print_winner(void)
{
    for (int k=0; k<candidate_count; k++)
    {
        if(candidates[k].votes>(candidates[k+1].votes||candidates[k-1].votes))
        {
            printf("%s\n",candidates[k].name);
        }
    }
}
