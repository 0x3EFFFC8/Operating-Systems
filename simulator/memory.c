#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
 
memory * createList(){
    memory * tmp;
    tmp = malloc(sizeof(memory));
    tmp -> head = NULL;
    tmp -> tail = NULL;
    return tmp;
}

unsigned empty(memory* tmp) {
    return (tmp -> head == NULL) && (tmp -> tail == NULL);
}

void insertFirst(memory * tmp, int addr, int band, int data, char * inst[5]) {
    Node * node;
    node = malloc(sizeof(Node));
    node -> addr = addr;
    node -> band = band;
    node -> data = data;
    for (int i=0; i < 5; i++){
        node -> inst[i] = inst[i];
    }
    node -> next = tmp -> head;
    node -> prev = NULL;
    if (empty(tmp)) 
        tmp -> tail = node;
    else
        tmp -> head -> prev = node;
    tmp -> head = node;
}

Node* findNode(memory * tmp, int addr) {
    Node * node = tmp -> head;
    while (node && node -> addr != addr){
        node = node -> next;
    }
    return node;
}
 
void Print(memory *mem) {
	Node * tmp = mem -> tail;
	while(tmp != NULL) {
    if (tmp -> band != 1){
        printf("%d : %d\n",tmp -> addr, tmp -> data);
    } else {
        printf("%d : ",tmp -> addr);
        for (int i=0; i < 5; i++){
            printf("%s ",tmp -> inst[i]);
        }
        printf("\n");
    }
		tmp = tmp -> prev;
	}
}

void freeList(memory *tmp) {
    Node *current = tmp -> head;
    Node *next;

    while (current != NULL) {
        next = current -> next;
        free(current);
        current = next;
    }

    tmp->head = NULL;
    tmp->tail = NULL;
}
