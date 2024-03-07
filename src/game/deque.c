#include "deque.h"
#include <stdlib.h>

Node* node_create(void* data)
{
    Node* n = malloc(sizeof(Node));
    n->data = data;
    n->next = n->prev = NULL;
    return n;
}

Deque deque_create(void)
{
    Deque dq;
    dq.head = NULL;
    dq.tail = NULL;
    return dq;
}

void deque_insert(Deque* dq, Node* n)
{
    if (dq->head == NULL) {
        dq->head = dq->tail = n;
        n->next = n->prev = NULL;
    } else {
        n->prev = dq->tail;
        n->next = NULL;
        dq->tail = dq->tail->next = n;
    }
}

void deque_remove(Deque* dq, Node* n)
{
}
