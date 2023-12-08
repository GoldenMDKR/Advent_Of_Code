#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <err.h>

// IDC about th ememory leak!!!


// Copy from TP
struct htab
{
    size_t capacity;
    size_t size;
    struct pair *data;
};

struct element {
    char* left;
    char* right;
};

struct pair
{
    uint32_t hkey;
    char *key;
    struct element *value;
    struct pair *next;
};


uint32_t hash(char *key)
{
    size_t i = 0;
    uint32_t hash = 0;
    while (key[i] != '\0') {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}


struct htab *htab_new()
{
    struct pair* new_pair = calloc(4, sizeof(struct pair));
    struct htab* new_htab = malloc(sizeof(struct htab));
    if (!new_pair || !new_htab)
        errx(1, "Not enough memory!");
    new_htab->capacity=4;
    new_htab->size=0;
    new_htab->data = new_pair;
    return new_htab;
}

void htab_clear(struct htab *ht)
{
    for (size_t i = 0; i<ht->capacity; i++) {
         struct pair *currp = ht->data[i].next;
         ht->data[i].next=NULL;
         while (currp != NULL) {
            struct pair *temp = currp->next;
            free(currp);
            currp=temp;
         }
    }
    ht->size=0;
}

void htab_free(struct htab *ht)
{
    htab_clear(ht);
    free(ht->data);
    free(ht);
}

void htab_clear_final(struct htab *ht)
{
    for (size_t i = 0; i<ht->capacity; i++) {
         struct pair *currp = ht->data[i].next;
         ht->data[i].next=NULL;
         while (currp != NULL) {
            struct pair *temp = currp->next;
            free(currp->value->right);
            free(currp->value->left);
            free(currp->value);
            free(currp->key);
            free(currp);
            currp=temp;
         }
    }
    ht->size=0;
}
void htab_free_final(struct htab *ht)
{
    htab_clear_final(ht);
    free(ht->data);
    free(ht);
}
struct pair *htab_get(struct htab *ht, char *key)
{
    uint32_t hashk = hash(key);
    size_t index = hashk % ht->capacity;
    struct pair* currp = ht->data[index].next;
    while (currp != NULL && currp->hkey != hashk )
        currp = currp->next;
    return currp;

}

int htab_insert(struct htab *ht, char *key, struct element *value)
{
    // verify id elem exist
    if (htab_get(ht,key))
        return 0;
    
    // create the new pair and fill it with its value 
    struct pair* new_pair = malloc(sizeof(struct pair));
    new_pair->hkey=hash(key);
    new_pair->key=key;
    new_pair->value=value;
    size_t index = new_pair->hkey % ht->capacity;
    struct pair* sentinel = &ht->data[index];
    new_pair->next=sentinel->next;
    // update the sentinel
    sentinel->next=new_pair;

    //verify if the size need to be doubled
    if (new_pair->next)
        return 1;
    ht->size++;
    if (100 * ht->size / ht->capacity <= 75)
        return 1;

    //double the size if needed
    struct pair* doubled_pairs = calloc(ht->capacity*2, sizeof(struct pair));
    struct pair* old_pairs = ht->data;
    struct htab to_clear = {
        ht->capacity,
        ht->size,
        old_pairs
    };

    // create the new data for

    ht->data = doubled_pairs;
    ht->capacity *= 2;
    ht->size =0;
    for (size_t i = 0; i < ht->capacity / 2; i++) {
        struct pair* temp= old_pairs[i].next;
        while (temp!=NULL) {
            htab_insert(ht, temp->key, temp->value);
            temp = temp->next;
        }
    }

    //free the old data
    htab_clear(&to_clear);
    free(to_clear.data);
    return 1;
    
}

void htab_remove(struct htab *ht, char *key)
{
    if (!htab_get(ht, key))
        return;
    uint32_t hashk = hash(key);
    size_t index = hashk % ht->capacity;
    struct pair* currp = ht->data[index].next;
    struct pair* prev_currp = &ht->data[index];
    while (currp->hkey != hashk )
    {
        prev_currp = currp;
        currp = currp->next;
    }
    prev_currp->next=currp->next;
    if(!ht->data[index].next)
        ht->size--;
    free(currp);
}
// end of copy



char* get_next_char(char** c){
    for (;;(*c)++)
    {
        if (**c == '\0')
            return 0;
        if (**c >= 'A' && **c<='Z')
            break;
    }
    char* stri = calloc(300,sizeof(char));
    int count = 0;
    while (**c >= 'A' && **c<='Z')
    {    
        stri[count] = **c;
        count++;
        (*c)++;
    }
    return stri;


}

int main(){
    FILE* fptr = fopen("input.txt","r");
    char* input;
    int step = 0;
    char buffer[1024];
    input = fgets(buffer,1024,fptr);
    char* left_right = get_next_char(&input);
    struct htab* h_tab = htab_new();
    for(int i = 0;(input = fgets(buffer,1024,fptr)); i++){
        if (*input == '\n')
        {   
            i--;
            continue;
        }
        char* name = get_next_char(&input); 
        char* left = get_next_char(&input); 
        char* right = get_next_char(&input); 
        struct element *curr_elem = calloc(1, sizeof(struct element));
        curr_elem->left = left;
        curr_elem->right = right;

        htab_insert(h_tab,name,curr_elem);

    }

    struct pair* curr_pair = htab_get(h_tab,"AAA");
    int i = 0;
    while(strcmp(curr_pair->key, "ZZZ"))
    {
        if (left_right[i] == 'L')
            curr_pair = htab_get(h_tab,curr_pair->value->left);
        else
            curr_pair = htab_get(h_tab,curr_pair->value->right);
        i = (i+1) % strlen(left_right);
        step++;
    }

    htab_free_final(h_tab);

    printf("%i\n",step);

    return 0;
}