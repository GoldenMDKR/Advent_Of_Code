#include <string.h>
#include <stdio.h>


int is_digit(char* s)
{
    if (s[0]>='0' && s[0]<='9')
        return s[0]-'0';
    if (!strncmp(s,"one",3))
        return 1;
    if (!strncmp(s,"two",3))
        return 2;
    if (!strncmp(s,"three",5))
        return 3;
    if (!strncmp(s,"four",4))
        return 4;
    if (!strncmp(s,"five",4))
        return 5;
    if (!strncmp(s,"six",3))
        return 6;
    if (!strncmp(s,"seven",5))
        return 7;
    if (!strncmp(s,"eight",5))
        return 8;
    if (!strncmp(s,"nine",4))
        return 9;
    return -1;
}


void main(){
    FILE *fptr = fopen("input.txt","r");
    char *input;
    int sum = 0;
    char buffer[1024];
    input = fgets(buffer,1024,fptr);
    while (input)
    {
        int i = -1;
        int j = -1;
        int index = 0;
        while (i==-1)
        {
            i = is_digit(input+index);
            index++;
        }
        index = 0;
        while (index<strlen(input))
        {
            int temp = is_digit(input+index);
            if (temp != -1)
                j = temp;
            index++;
        }
        sum += i*10 + j;

        input = fgets(buffer,1024,fptr);
    }

    printf("%i\n",sum);

    fclose(fptr);
}


