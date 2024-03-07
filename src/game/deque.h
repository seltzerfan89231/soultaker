#ifndef DEQUE_H
#define DEQUE_H

#include <gvec.h>

typedef struct Node {
    void* data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct Deque {
    struct Node* head;
    struct Node* tail;
} Deque;

Node* node_create(void* data);
Deque deque_create(void);
void deque_insert(Deque* dq, Node* n);
void deque_remove(Deque* dq, Node* n);

#endif