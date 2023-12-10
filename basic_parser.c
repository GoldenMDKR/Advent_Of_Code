#include <string.h>
#include <stdio.h>

int get_next_int(char** c){
    for (;;(*c)++)
    {
        if (**c == '\0')
            return 0;
        if (**c >= '0' && **c<='9')
            break;
    }
    int num = 0;
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
    int curr_num;
    int sum = 0;
    char buffer[1024];
    while((input = fgets(buffer,1024,fptr))){
        
    }

    printf("%i",sum);

    return 0;
}