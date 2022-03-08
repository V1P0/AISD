#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <intrin.h>

#define basicReturn 0;


typedef struct list {
    struct list *next;
    int val;
} list;

void addStart(int val, list **start) {
    list *new = malloc(sizeof(list));
    new->val = val;
    new->next = *start;
    *start = new;
}

void addEnd(int val, list **start) {
    list *current = *start;
    if (current == NULL) {
        addStart(val, start);
        return;
    }
    while (current->next != NULL) {
        current = current->next;
    }
    list *new = malloc(sizeof(list));
    new->val = val;
    current->next = new;
    new->next = NULL;
}

int length(list *start) {
    int k = 0;
    while (start != NULL) {
        start = start->next;
        k++;
    }
    return k;
}

void add(int val, list **start, int n) {
    list *current = *start;
    if(n<0) return;
    if(n == 0){
        addStart(val, start);
        return;
    }
    for (int i = 1; i < n; i++) {
        current = current->next;
        if (current == NULL) return;
    }
    list *new = malloc(sizeof(list));
    new->val = val;
    new->next = current->next;
    current->next = new;

}

void delete(list **start, int n){
    list *current = *start;
    if(n<0 || current == NULL) return;
    if(n==0){
        *start = current->next;
        return;
    }
    for (int i = 1; i < n; i++) {
        current = current->next;
        if (current == NULL) return;
    }
    if(current->next == NULL) return;
    list* temp = current->next;
    current->next = current->next->next;
    free(temp);
}

void merge(list** list1, list* list2){
    list* current = *list1;
    if(current == NULL) *list1 = list2;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = list2;
}

int get(list *start, int n) {
    if (n < 0) return basicReturn;
    for (int i = 0; i < n; i++) {
        start = start->next;
        if (start == NULL) return basicReturn;
    }
    return start->val;

}

void freeList(list *start) {
    list *next;
    while (start != NULL) {
        next = start->next;
        free(start);
        start = next;
    }
}

void printList(list *start) {
    while (start != NULL) {
        printf("%d\n", start->val);
        start = start->next;
    }
}

int contains(list* start, int val){
    int k = 0;
    while (start != NULL) {
        if(start->val == val) return k;
        k++;
        start = start->next;
    }
    return -1;
}

void getTime(list* start, int n, int test_count){
    unsigned __int64 t1, t2;
    unsigned __int64 sum = 0;
    for(int i = 0; i<test_count; i++){
        t1 = __rdtsc();
        get(start, n);
        t2 = __rdtsc();
        sum += (t2-t1);
    }
    sum = sum/test_count;
    printf("%d;%llu\n",n , sum);
}

int main() {
    list *start = NULL;
    srand(time(NULL));
    int amount = 1000;
    for(int i = 0; i<amount; i++){
        addStart(rand(), &start);
    }
    for(int i = 0 ; i<amount;i+=4){
        getTime(start, i, 1000);
    }
    freeList(start);
    return 0;
}