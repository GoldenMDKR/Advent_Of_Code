#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// please neaver again
// it's dumb but it work
// iter trough each seed range by increment of 1000
// will find a seed wich is at most 1000 bigger than the correct one
// the use the script form the fisrt part to test the 1000 previous seed
// will find the precise minimum
// i could make this part automatic
// but at this pont i just want all this to be over
// HAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

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
    char* seed_input = calloc(1024, sizeof(char));
    char buffer[1024];
    input = fgets(buffer,1024,fptr);
    strncpy(seed_input,input,1024);
    input = fgets(buffer,1024,fptr);


    //create the maps
    long dest[7][100] = {[0 ... 6][0 ... 99] = -1};
    long source[7][100] = {[0 ... 6][0 ... 99] = -1};
    long range[7][100] = {[0 ... 6][0 ... 99] = -1};
    int process =0;
    int iter=0;
    while((input = fgets(buffer,1024,fptr))){
        if (*input == '\n')
        {
            process++;
            iter = 0;
            continue;
        }
        if (*input < '0' || *input > '9')
            continue;

        dest[process][iter] = get_next_int(&input);
        source[process][iter] = get_next_int(&input);
        range[process][iter] = get_next_int(&input);


        iter++;
    }

    long min = -1;
    long min_iter;
    long curr_seed;
    long next;
    for (int i = 0; (curr_seed = get_next_int(&seed_input)) != -1; i++)
    {

        next = get_next_int(&seed_input);
        for(long this_iter = curr_seed; this_iter < curr_seed+next; this_iter+=1000)
        {
            long this_seed = this_iter;

            for (int i = 0;  i<7; i++)
            {
                for (int j = 0; source[i][j]!=-1;j++)
                {
                    if (this_seed>=source[i][j] && this_seed <= source[i][j]+range[i][j])
                    {
                        this_seed = dest[i][j] + (this_seed - source[i][j]);

                        break;
                    }
                }


            }
            if (min == -1)
                min = this_seed;
            min_iter = min > this_seed ? this_iter : min_iter;
            min = min > this_seed ? this_seed : min;
            printf("%li, min : %li\n",this_iter, min);

        }
    }
    
    printf("%li, %li\n", min_iter, min);
    return 0;
}