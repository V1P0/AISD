#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//value that's returned from pop if list is empty
#define basicReturn 0;

//LIFO
typedef struct list{
    struct list* next;
    int val;
}list;

void push(int val, list** start){
    list* newNode = malloc(sizeof(list));
    newNode->next = *start;
    *start = newNode;
    newNode->val = val;
}

int pop(list** start){
    if(*start == NULL) return basicReturn;
    int val = (*start)->val;
    list* temp = (*start)->next;
    free(*start);
    *start = temp;
    return val;
}

void freeList(list* start){
    list* next;
    while(start != NULL){
        next = start->next;
        free(start);
        start = next;
    }
}

int main() {
    int amount = 100;
    list* start = NULL;
    srand(time(NULL));
    for(int i = 0; i<amount; i++){
        int val = rand();
        push(val, &start);
        printf("pushed %d\n", val);
    }
    printf("-----------------\n");
    for(int i = 0; i<amount; i++){
        int val = pop(&start);
        printf("popped %d\n", val);
    }
    return 0;
}
