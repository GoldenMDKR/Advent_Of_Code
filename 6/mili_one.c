#include <string.h>
#include <stdio.h>

long get_next_int(char** c){
    for (;;(*c)++)
    {
        if (**c == '\0')
            return 0;
        if (**c >= '0' && **c<='9')
            break;
    }
    long num = 0;
    while ((**c >= '0' && **c<='9') || **c == ' ')
    {    
        if (**c == ' ')
        {
            (*c)++;
            continue;
        }
        num = num*10 + (**c)-'0';
        (*c)++;
    }
    return num;


}

int main(){
    FILE* fptr = fopen("input.txt","r");
    char* input;
    char buffer[1024];
    input = fgets(buffer,1024,fptr);
    long time = get_next_int(&input);
    input = fgets(buffer,1024,fptr); 
    long dist = get_next_int(&input);

    int nb_win = 0;
    for(long  j = 0; j<time;j++)
        if (j*(time-j) > dist) 
            nb_win++;
    
    printf("%i",nb_win);

    return 0;
} 