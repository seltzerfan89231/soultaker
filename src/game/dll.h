#ifndef dll_H
#define dll_H

#include <gvec.h>
#include <gtype.h>

typedef struct Node {
    void* data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct Dll {
    struct Node* head;
    struct Node* tail;
} Dll;

Node* node_create(void* data);
Dll dll_create(void);
i2 dll_empty(Dll* dq);
void dll_append(Dll* dq, Node* n);
void dll_remove(Dll* dq, Node* n);

#endif