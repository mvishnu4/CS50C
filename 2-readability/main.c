#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char str_text[1000];
    printf("TEXT: ");
    scanf("%[^\n]%*c", str_text);
    int l = 0;
    int w = 1;
    int s = 0;
    for (int i=0; i<strlen(str_text); i++)
    {
        if (isalpha(str_text[i]))
        {
            l++;
        }
    }
    for (int i=0; i<strlen(str_text); i++)
    {
        if (isspace(str_text[i]))
        {
            w++;
        }
    }
    for (int i=0; i<strlen(str_text); i++)
    {
        if (str_text[i] == '.' || str_text[i] == '?' || str_text[i] == '!')
        {
            s++;
        }
    }
    printf("%i\n", l);
    printf("%i\n", w);
    printf("%i\n", s);
    
    int L = (l*100)/w;
    int S = (s*100)/w;
    
    int index = 0.0588 * L - 0.296 * S - 15.8;
    
    if (index<1)
    {
        printf("grade less than 1\n");
    }
    else if (index>16)
    {
        printf("grade 16+\n");
    }
    else
    {
        printf("grade %i\n", index);
    }
}
        

