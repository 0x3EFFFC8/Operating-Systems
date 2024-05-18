#ifndef MEMORY_H
#define MEMORY_H

struct Node {
    int addr;
    int band;
    int data;
    char * inst[5];   
    struct Node * next;
    struct Node * prev;
};

struct memory {
    struct Node * head;
    struct Node * tail;    
};

typedef struct Node Node;
typedef struct memory memory;

memory * createList();
unsigned empty(memory * tmp);
void insertFirst(memory * tmp, int addr, int band, int data, char * inst[5]);
Node* findNode(memory * Node, int addr);
void Print(memory *mem);
void freeList(memory *tmp);

#endif
