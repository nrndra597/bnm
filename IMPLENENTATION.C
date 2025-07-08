#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
} LinkedList;


LinkedList* create_list();
void insert_front(LinkedList* list, int value);
void insert_end(LinkedList* list, int value);
int delete_value(LinkedList* list, int value);
void print_list(const LinkedList* list);
void free_list(LinkedList* list);

#endif

#include <stdio.h>
#include <stdlib.h>

LinkedList* create_list() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

void insert_front(LinkedList* list, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = list->head;
    list->head = new_node;
}

void insert_end(LinkedList* list, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    if (list->head == NULL) {
        list->head = new_node;
        return;
    }
    Node* temp = list->head;
    while (temp->next) temp = temp->next;
    temp->next = new_node;
}

int delete_value(LinkedList* list, int value) {
    Node *temp = list->head, *prev = NULL;
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return 0; 
    if (prev == NULL) list->head = temp->next;
    else prev->next = temp->next;
    free(temp);
    return 1; 
}

void print_list(const LinkedList* list) {
    Node* temp = list->head;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void free_list(LinkedList* list) {
    Node* temp = list->head;
    while (temp) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    free(list);
}

#include <stdio.h>

int main() {
    LinkedList* list = create_list();
    insert_end(list, 10);
    insert_front(list, 5);
    insert_end(list, 20);
    print_list(list); 

    delete_value(list, 10);
    print_list(list); 

    free_list(list);
    return 0;
}
