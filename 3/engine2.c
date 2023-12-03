#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Gear {
    int i;
    int j;
    int sum;
    int count;
    struct Gear* next;
};

struct Gear Gear_list =  {
    -1,
    -1,
    0,
    0,
    NULL,
};

void gear_add(int i, int j, int num)
{
    struct Gear* curr_gear = &Gear_list;
    struct Gear* prev_gear = NULL;
    while(curr_gear)
    {
        if (curr_gear->i == i && curr_gear->j == j)
        {
            curr_gear->sum *= num;
            curr_gear->count++;
            return;
        }
        prev_gear = curr_gear;
        curr_gear = curr_gear->next;
    }
    struct Gear* new = malloc(sizeof(struct Gear));
    new->i = i;
    new->j = j;
    new->sum = num;
    new->count = 1;
    new->next = NULL;

    prev_gear->next = new;
    return;
}



int symbol(char* c, char* prev, char* next, int* i, int* l)
{

    if (*prev !='\0')
        for (int j = (*i)-1; j <= (*i)+1; j++)
            if (prev[j] == '*')
            {
                (*l)--;
                return j;
            }
    if (*next !='\0')
        for (int j = (*i)-1; j <= (*i)+1; j++)
            if (next[j] == '*')
            {
                (*l)++;
                return j;
            }
    for (int j = (*i)-1; j <= (*i)+1; j++)
            if (c[j] == '*')
                return j;
    return -1;
}

int get_next_int(char* c, char* prev, char* next, int* i, int l){
    for (;;(*i)++)
    {
        if (*(c+*i) == '\0')
            return 0;
        if (*(c+*i) >= '0' && *(c+*i)<='9')
            break;
    }
    int num = 0;
    int geari = -1;
    int gearj = -1;
    while (*(c+*i) >= '0' && *(c+*i)<='9')
    {    
        int templ = l;
        int j = symbol(c, prev, next, i, &templ);
        if (j != -1)
        {
            gearj = j;
            geari = templ;
        }
        num = num*10 + *(c+*i) -'0';
        (*i)++;
    }
    if (gearj != -1)
        gear_add(geari, gearj, num);
    return num;
}

int main(){
    FILE* fptr = fopen("input.txt","r");
    int curr_num;
    int sum = 0;
    char buffer[1024];
    char prev_input[1024];
    prev_input[0] = '\0';
    char input[1024];
    input[0] = '\0';
    char* next_input = fgets(buffer,1024,fptr);
    strcpy(input,next_input);
    next_input = fgets(buffer,1024,fptr);

    int l = 0;

    while(*input != '\0'){

        int i = 0;


        while ((curr_num = get_next_int(input, prev_input, next_input, &i, l)));        

        strcpy(prev_input,input);
        strcpy(input,next_input);
        next_input = fgets(buffer,1024,fptr);
        if (!next_input)
            next_input = "\0";
        l++;
    }
    for (struct Gear* curr = &Gear_list; curr; curr = curr->next)
    {

        if (curr->count == 2)
        
            sum += curr->sum;
    }

    printf("%i",sum);

    fclose(fptr);

    return 0;
}