#include <stdio.h>
#include <stdlib.h>

typedef struct hashnode{
    int key;
    int* value;
    struct hashnode* next;
} hashnode;

int* find(hashnode* head, int key){
    hashnode* current = head;
    while(current != NULL){
        if(current->key == key) return current -> value;
        current = current->next;
    }
    return NULL;
}

void insert(hashnode** head, int key, int* value){
    hashnode* current = *head;

    while(current != NULL){
        if(current->key == key){
            current->value = value;
            return;
        }
        current = current->next;
    }
    hashnode* new = malloc(sizeof(hashnode));
    new->key = key;
    new->value = value;

    new->next = *head;
    *head = new;
}


int main(){
    hashnode* head = NULL;
    int a = 20;
    int c = 40;
    int d  = 2;

    insert(&head, 1, &a);
    insert(&head, 1, &c);
    insert(&head, 1, &d);

    int* b = find(head, 1);

    printf("%d", *b);

    return 0;
}