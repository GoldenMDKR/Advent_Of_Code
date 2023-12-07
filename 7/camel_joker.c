#include <stdio.h>

struct hand {
    int card[5];
    int strength;
    int bid;
    int rank;
};

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


void get_card(struct hand *h, char** c)
{
    for(int i = 0; i<5; i++)
    {
        char temp = **c;
        switch (temp){
            case 'A' : 
                h->card[i] = 14;
                break;
            case 'K' : 
                h->card[i] = 13;
                break;
            case 'Q' : 
                h->card[i] = 12;
                break;
            case 'J' : 
                h->card[i] = 1;
                break;
            case 'T' : 
                h->card[i] = 10;
                break;
            default : 
                h->card[i] = temp-'0';
                break;
        }
        (*c)++;
    }

}



void set_strength(struct hand *h)
{
    int count[15] = {[0 ... 14] = 0};
    for(int i = 0; i<5; i++)
    {
        count[h->card[i]]++;
    }
    if (count[1] == 5)
    {
        h->strength = 6;
        return;
    }
    int max = 0;
    int max_i = 0;
    for(int i = 2; i<15; i++)
    {
        max = count[i] >= max ? count[i] : max;
        max_i = count[i] >= max ? i : max_i;
    }
    
    count[max_i] += count[1];


    // check each type 
    for(int i = 2; i<15; i++)
    {    
        if (count[i] == 5)
        {
            h->strength = 6;
            return;
        }
        if (count[i] == 4)
        {
            h->strength = 5;
            return;
        }
        if (count[i] == 3)
        {
            for(int j = 2; j<15; j++)
                if (count[j] == 2)
                {
                    h->strength = 4;
                    return;
                }
            h->strength = 3;
            return;
        }
        if (count[i] == 2)
        {
            for(int j = 2; j<15; j++)
            {   
                if (i == j)
                    continue;
                if (count[j] == 3)
                {
                    h->strength = 4;
                    return;
                }
                if (count[j] == 2)
                {
                    h->strength = 2;
                    return;
                }
            }
            h->strength = 1;
            return;
        }
    }
    h->strength = 0;
    return;    
}


int main(){
    FILE* fptr = fopen("input.txt","r");
    char* input;
    char buffer[1024];
    struct hand hands[1000]; 
    int count = 0;
    long sum = 0;
    while((input = fgets(buffer,1024,fptr))){
        get_card(&hands[count],&input);
        hands[count].bid = get_next_int(&input);
        set_strength(&hands[count]);
        hands[count].rank = 1;
        count++;
    }

    for(count = 0; count<1000; count++)
    {
        for(int i = 0; i<1000; i++)
        {

            if (count == i)
                continue;
            if (hands[count].strength > hands[i].strength)
                hands[count].rank++;
            else if (hands[count].strength == hands[i].strength)
                for(int j = 0; j<5; j++)
                {
                    if (hands[count].card[j] > hands[i].card[j])
                    {
                        hands[count].rank++;
                        break;
                    }
                    if (hands[count].card[j] < hands[i].card[j])
                        break;
                }
        }
        sum += hands[count].bid * hands[count].rank;
    }

    printf("%li\n", sum);
    return 0;
}