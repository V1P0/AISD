#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define basicReturn 0;

typedef struct dlist{
    struct dlist* prev;
    struct dlist* next;
    int val;
}list;

typedef struct fifo{
    list* start;
    list* end;
}fifo;

void push(int val, fifo* queue){
    list* node = malloc(sizeof(list));
    node->val = val;
    node->prev = NULL;
    node->next = queue->start;
    if(queue->start != NULL){
        queue->start->prev = node;
    } else{
        queue->end = node;
    }
    queue->start = node;
}

int pop(fifo* queue){
    list* node = queue->end;
    if(node == NULL) return basicReturn;
    int val = queue->end->val;
    queue->end = queue->end->prev;
    free(node);
    return val;
}

int main(){
    int amount = 100;
    fifo* queue = malloc(sizeof(fifo));
    queue->start = NULL;
    srand(time(NULL));
    for(int i = 0; i<amount; i++){
        int val = rand();
        push(val, queue);
        printf("pushed %d\n", val);
    }
    printf("-----------------\n");
    for(int i = 0; i<amount; i++){
        int val = pop(queue);
        printf("popped %d\n", val);
    }
    free(queue);
    return 0;
}

