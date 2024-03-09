#include "dll.h"
#include <stdlib.h>

Data* data_create(void* obj)
{
    Data* d = malloc(sizeof(Data));
    d->obj = obj;
    return d;
}

void data_destroy(Data* d)
{
    free(d->node);
    free(d->obj);
    free(d);
}

DLLNode* dll_node_create(Data* d)
{
    DLLNode* n = malloc(sizeof(DLLNode));
    n->data = d, d->node = n;
    n->next = n->prev = NULL;
    return n;
}

DLL dll_create(void)
{
    DLL dll;
    dll.head = NULL;
    return dll;
}

i2 dll_empty(DLL* dll)
{
    return dll->head == NULL;
}

void dll_push(DLL* dll, DLLNode* n)
{
    if (dll->head == NULL) {
        dll->head = n;
        n->next = n->prev = NULL;
    } else {
        n->prev = NULL;
        n->next = dll->head;
        dll->head->prev = n;
        dll->head = n;
    }
}

void dll_remove(DLL* dll, DLLNode* n)
{
    if (dll->head == n)
        dll->head = n->next;
    if (n->next != NULL)
        n->next->prev = n->prev;
    if (n->prev != NULL)
        n->prev->next = n->next;
}
