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
        get_next_int(&input);
        int r = 0;
        int g = 0;
        int b = 0;
        while((curr_num = get_next_int(&input)))
        {
            input ++;
            switch (*input){
                case 'r' :
                    if (r < curr_num)
                        r = curr_num;
                    break;
                case 'g' :
                    if (g < curr_num)
                        g = curr_num;
                    break;
                case 'b' :
                    if (b < curr_num)
                        b = curr_num;
                    break;
            }
        }
        sum += r*g*b;
    }

    printf("%i",sum);

    return 0;
}