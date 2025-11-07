#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode{
    int value;
    struct listNode* next;
} listNode;

listNode* create_node(int value){
    listNode* newNode = malloc(sizeof(listNode));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void append_node(listNode** head, int value){
    listNode* newNode = create_node(value);
    if (*head == NULL){
        *head= newNode;
        return;
    }
    listNode* current = *head;

    while(current->next != NULL){
        current = current->next;
    }
    current->next = newNode;
}

void show_linked_list(listNode** head){
    listNode* current = (*head);
    while(current->next != NULL){
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("%d", current->value);
}

int main(){
    listNode* head = NULL;
    for (int i=1; i <= 10; i++){
        append_node(&head, i);
    }
    show_linked_list(&head);
    return 0;
}