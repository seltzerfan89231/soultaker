#include "dll.h"
#include <stdlib.h>

Data* data_create(void* val, u32 offset, buffertype type)
{
    Data* d = malloc(sizeof(Data));
    d->val = val;
    d->offset = offset;
    d->type = type;
    return d;
}

void data_destroy(Data* d)
{
    free(d);
}

DLLNode* dll_node_create(Data* d)
{
    DLLNode* n = malloc(sizeof(DLLNode));
    n->data = d, d->node = n;
    n->next = n->prev = NULL;
    return n;
}

void dll_node_destroy(DLLNode* n)
{
    free(n);
}

DLL dll_create(void)
{
    DLL dll;
    dll.head = dll.tail = NULL;
    return dll;
}

i2 dll_empty(DLL* dll)
{
    return dll->head == NULL;
}

void dll_push(DLL* dll, DLLNode* n)
{
    if (dll->head == NULL) {
        dll->head = dll->tail = n;
        n->next = n->prev = NULL;
    } else {
        n->prev = dll->tail;
        n->next = NULL;
        dll->tail->next = n;
        dll->tail = n;
    }
}

void dll_remove(DLL* dll, DLLNode* n)
{
    if (dll->head == n)
        dll->head = n->next;
    if (dll->tail == n)
        dll->tail = n->prev;
    if (n->next != NULL)
        n->next->prev = n->prev;
    if (n->prev != NULL)
        n->prev->next = n->next;
}

void dll_replace(DLL* dll, DLLNode* n)
{
    DLLNode *tail, *new_tail;
    tail = dll->tail, new_tail = tail->prev;
    tail->prev = n->prev, tail->next = n->next;
    if (n->next != NULL)
        n->next->prev = tail;
    if (n->prev != NULL)
        n->prev->next = tail;
    else
        dll->head = tail;
    if (new_tail != NULL)
        new_tail->next = NULL;
    else
        dll->head = NULL;
    dll->tail = new_tail;
}