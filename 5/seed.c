#include <string.h>
#include <stdio.h>



long min(long* seeds)
{
    long min = seeds[0];
    for(int i = 1; seeds[i] != -1; i++)
    {
        if (seeds[i]<min)
            min = seeds[i];
    }
    return min;
}

long get_next_int(char** c){
    for (;;(*c)++)
    {
        if (**c == '\0')
            return -1;
        if (**c >= '0' && **c<='9')
            break;
    }
    long num = 0;
    while (**c >= '0' && **c<='9')
    {    
        num = num*10 + (**c)-'0';
        (*c)++;
    }
    return num;


}

int main(){
    FILE* fptr = fopen("input.txt","r");
    char* input;
    char buffer[1024];
    long seeds[1011] = {[0 ... 1010] = -1};
    input = fgets(buffer,1024,fptr);


    long curr_seed;
    for (int i = 0; (curr_seed = get_next_int(&input)) != -1; i++)
    {
        seeds[i] = curr_seed;
    }
    

    long dest[100] = {[0 ... 99] = -1};
    long source[100] = {[0 ... 99] = -1};
    long range[100] = {[0 ... 99] = -1};
    int iter=0;

    while((input = fgets(buffer,1024,fptr))){

        // detect map change
        if (*input == '\n')
        {
            for (int i = 0; seeds[i] != -1; i++)
            {
                for (int j = 0; source[j]!=-1;j++)
                {
                    if (seeds[i]>=source[j] && seeds[i] <= source[j]+range[j])
                    {
                        seeds[i] = dest[j] + (seeds[i] - source[j]);
                        break;
                    }
                }
            }

            // set back map to -1
            for (int j = 0; source[j]!=-1;j++)
            {
                source[j] = -1;
                dest[j] = -1;
                range[j] = -1;
            }
            iter = 0;
            continue;
        }
        // skip text
        if (*input < '0' || *input > '9')
            continue;
        // create map
        dest[iter] = get_next_int(&input);
        source[iter] = get_next_int(&input);
        range[iter] = get_next_int(&input);
        iter++;
    }
    printf("%li\n", min(seeds));
    return 0;
}