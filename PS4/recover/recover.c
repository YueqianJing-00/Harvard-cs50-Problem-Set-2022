#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>
#include <string.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if( argc != 2)
    {
        printf("Usage: ./recover Image\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    u_int8_t buffer[BLOCK_SIZE];
    int flag = 0;
    char filename[8];
    FILE *img;

    while(fread(&buffer, BLOCK_SIZE, 1, file))
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff){
            if(buffer[3] >= 0xe0 && buffer[3] <= 0xef){
                printf("Found JPEG\n");
                if(flag > 0){
                    fclose(img);
                    sprintf(filename, "%03i.jpg", flag);
                    img = fopen(filename, "w");
                    printf("Found JPEG\n");
                    fwrite(&buffer, BLOCK_SIZE, 1, img);
                    flag++;
                } 
                else{
                    img = fopen("000.jpg", "w");
                    fwrite(&buffer, BLOCK_SIZE, 1, img);
                    flag++;
                }
            }
        }
        else if (flag > 0)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, img);
        }
    }
    fclose(file);
    fclose(img);
    return 0;
}