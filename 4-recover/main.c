#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover %s\n", argv[1]);
        return 1;
    }
    
    FILE *file = fopen("/Users/madarapuvishnuvardhanrao/Desktop/Desktop/recover/card.raw","r");
    if (file == NULL)
    {
        return  1;
    }
    
    int i = 0;
    int buffer[512];
    char *jpg  = malloc(9 * sizeof(char));

    FILE *decimg = NULL;
    
    while (fread(buffer, (sizeof(int)*2)/8, 512, file) == 512)
    {
        //printf("%x\n", buffer[0]);
        if (buffer[0] == 0xe0ffd8ff)// & buffer[1] == 0x8d && buffer[2] == 0xff)// && (buffer[3] & 0xff) == 0xe0)
        {
            printf("%i %x\n",i,buffer[0]);
            sprintf(jpg, "%03i.jpg",i);
            decimg = fopen(jpg, "w");
            fwrite(buffer, sizeof(int)/4, 512, decimg);
            i++;
            //printf("%i",i);
            
        }
        else
        {
            while (buffer[0] == 0Xe0ffd8ff)//&& buffer[1] == 0X8d && buffer[2] == 0Xff)// && (buffer[3] & 0Xff) == 0Xe0)
            {
                printf("q");
                fwrite(buffer, (sizeof(int)*2)/8, 512, decimg);
            }
        }
    }
    
    fclose(file);
    free(jpg);
    fclose(decimg);
}
