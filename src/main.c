#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* cycles;
int cycles_count = 0;

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("ERROR: No file!\n");
        return 1;
    }
    FILE* file = fopen(argv[1], "r");
    size_t filesize = 0;
    while(fgetc(file) != EOF)
    {
        filesize++;
    }
    filesize++;
    rewind(file);
    char* fbuffer = malloc(filesize);
    fread(fbuffer, sizeof(char), filesize, file);
    fbuffer[filesize-1] = 0;

    unsigned char* buffer = malloc(30000);
    memset(buffer, 0, 30000);
    int pointer = 15000;

    for(int i = 0; i < filesize; i++)
    {
        switch(fbuffer[i])
        {
            case '>':
                pointer++;
                break;
            case '<':
                pointer--;
                break;
            case '+':
                buffer[pointer]++;
                break;
            case '-':
                buffer[pointer]--;
                break;
            case '.':
                putchar(buffer[pointer]);
                break;
            case ',':
                buffer[pointer] = getchar();
                break;
            case '[':
                if(buffer[pointer] != 0)
                {
                    cycles_count++;
                    int* temp = realloc(cycles, sizeof(int) * cycles_count);
                    temp[cycles_count-1] = i;
                    cycles = temp;
                }
                else
                {
                    int brackets = 1;
                    while(brackets > 0)
                    {
                        i++;
                        if(fbuffer[i] == '[') brackets++;
                        if(fbuffer[i] == ']') brackets--;
                    }
                }
                break;
            case ']':
                if(buffer[pointer] == 0)
                {
                    cycles_count--;
                    if(cycles_count > 0)
                    {
                        int* temp = realloc(cycles, sizeof(int) * cycles_count);
                        cycles = temp;
                    }
                    else
                    {
                        free(cycles);
                        cycles = NULL;
                    }
                    
                }
                else
                {
                    i = cycles[cycles_count-1];
                }
                break;
        }
    }
    fclose(file);
    free(fbuffer);
    free(buffer);
    putchar('\n');
    return 0;
}