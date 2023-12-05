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
        int curr_win[20];
        get_next_int(&input);
        int curr_point = 0;
        int i = 0;
        for (; *(input+1) != '|' ; i++)
            curr_win[i] = get_next_int(&input);
        
        while((curr_num = get_next_int(&input)))
            for (int j = 0; j<i; j++)
                if (curr_win[j] == curr_num)
                    curr_point = curr_point ? curr_point*2 : 1;
        
        
        sum += curr_point;
    }

    printf("%i",sum);

    return 0;
}