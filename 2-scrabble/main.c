#include <ctype.h>
#include <stdio.h>
#include <string.h>

int points[] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

int main(void)
{
    char str_word1[50];
    printf("player 1: ");
    scanf("%[^\n]%*c", str_word1);
    
    char str_word2[50];
    printf("player 2: ");
    scanf("%[^\n]%*c", str_word2);
    
    int score1 = 0;
    for (int i=0; i<strlen(str_word1); i++)
    {
        if (isupper(str_word1[i]))
        {
            score1 += points[str_word1[i] - 'A'];
        }
        else if (islower(str_word1[i]))
        {
            score1 += points[str_word1[i] - 'a'];
        }
        printf("%i", score1);
    }
    printf("\n");
    
    int score2 = 0;
    for (int i=0; i<strlen(str_word2); i++)
    {
        if (isupper(str_word2[i]))
        {
            score2 += points[str_word2[i] - 'A'];
        }
        else if (islower(str_word2[i]))
        {
            score2 += points[str_word2[i] - 'a'];
        }
        printf("%i", score2);
    }
    printf("\n");
    
    if (score1<score2)
    {
        printf("player 2 wins\n");
    }
    else if (score2<score1)
    {
        printf("player 1 wins\n");
    }
    else
    {
        printf("TIE!");
    }
}

