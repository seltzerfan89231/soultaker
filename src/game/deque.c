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

i2 deque_empty(Deque* dq)
{
    return dq->head == NULL;
}

void deque_append(Deque* dq, Node* n)
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
    if (dq->head == n)
        dq->head = n->next;
    if (dq->tail == n)
        dq->tail = n->prev;
    if (n->next != NULL)
        n->next->prev = n->prev;
    if (n->prev != NULL)
        n->prev->next = n->next;
}

Node* deque_pop(Deque* dq)
{
    if (dq->head != NULL) {
        Node* ret = dq->head;
        dq->head = ret->next;
        return ret;
    }
    return NULL;
}