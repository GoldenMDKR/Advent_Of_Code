#include <string.h>
#include <stdio.h>

int symbol(char* c, char* prev, char* next, int i)
{

    
        for (int j = i-1; j <= i+1; j++)
            if (prev[j] != '.' && (prev[j] <'0' || prev[j]>'9') && 
                prev[j]!= '\n' && prev[j]!= '\0')
                return 1;
        
    
        for (int j = i-1; j <= i+1; j++)
            if (next[j] != '.' && next[j] <'0' && next[j]>'9' && 
                next[j]!= '\n' && next[j]!= '\0')
                return 1;
    
    for (int j = i-1; j <= i+1; j++)
            if (c[j] != '.' && c[j] <'0' && c[j]>'9' && 
                c[j]!= '\n' && c[j]!= '\0')
                return 1;
    return 0;
}

int get_next_int(char* c, char* prev, char* next, int* i){
    for (;;(*i)++)
    {
        if (*(c+*i) == '\0')
            return 0;
        if (*(c+*i) >= '0' && *(c+*i)<='9')
            break;
    }
    int symb = 0;
    int num = 0;

    while (*(c+*i) >= '0' && *(c+*i)<='9')
    {    
        if (symbol(c, prev, next, *i))
            symb = 1;
        num = num*10 + *(c+*i) -'0';
        (*i)++;
    }
    printf("%i, %i \n", num, symb);
    return symb ? num : get_next_int(c,prev,next,i);


}

int main(){
    FILE* fptr = fopen("test.txt","r");
    int curr_num;
    int sum = 0;
    char buffer[1024];
    char prev_input[1024];
    strcpy(prev_input, "");
    char* next_input = fgets(buffer,1024,fptr);
    char input[1024];
    strcpy(input, next_input);
    next_input = fgets(buffer,1024,fptr);
    printf("%s \n %s\n", input, next_input);
    while(input){

        int i = 0;
        while ((curr_num = get_next_int(input, prev_input, next_input, &i)))
        {
            sum += curr_num;
        }
        strcpy(prev_input, input);
        strcpy(input, next_input);
        if (!next_input)
            strcpy(input,'\0');
        next_input = fgets(buffer,1024,fptr);
    }

    printf("%i",sum);

    return 0;
}