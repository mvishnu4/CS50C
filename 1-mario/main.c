//including header files
//#include <cs50.h>
#include <stdio.h>

//getting height from user to draw pyramid of valid height
int main(void)
{
    int h;
    do
    {
        printf("h:");
        scanf("%i",&h);
    }
    while(h<1 || h>8);

    for (int i=0; i<h; i++)
    {
        for (int s=0; s<h-i-1; s++)
        {
            printf(" ");
        }
        for (int j=0; j<i+1; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j=0; j<i+1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
