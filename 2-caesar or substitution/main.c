#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int key;
    printf("key:");
    scanf("%i", &key);
    
    //text
    char str_pt[100];
    printf("Plain Text:");
    scanf("%s", str_pt);
    
    //decoding with chip
    printf("chiperText:");
    for (int i=0; i<strlen(str_pt); i++)
    {
        if (isupper(str_pt[i]))
        {
            int n = (str_pt[i] + key - 'A')%26;
            printf("%c",65+n);
        }
        else if (islower(str_pt[i]))
        {
            int m = (str_pt[i] + key - 'a') % 26;
            printf("%c",97+m);
        }
        else
        {
            printf("%c",str_pt[i]);
        }
    }
    printf("\n");
}

