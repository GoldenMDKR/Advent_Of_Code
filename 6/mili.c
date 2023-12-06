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
    int sum = 1;
    int time[4];
    int dist[4];
    char buffer[1024];
    input = fgets(buffer,1024,fptr);
    for(int i = 0; i<4;i++)
        time[i] = get_next_int(&input);
    input = fgets(buffer,1024,fptr);
    for(int i = 0; i<4;i++)
        dist[i] = get_next_int(&input);

    for(int i = 0; i<4;i++)
    {
        int nb_win = 0;
        for(int j = 0; j<time[i];j++)
            if (j*(time[i]-j) > dist[i]) 
                nb_win++;
        sum *= nb_win;
    }
    printf("%i",sum);

    return 0;
}