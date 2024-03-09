#include "dll.h"
#include <stdlib.h>

Node* node_create(void* data)
{
    Node* n = malloc(sizeof(Node));
    n->data = data;
    n->next = n->prev = NULL;
    return n;
}

Dll dll_create(void)
{
    Dll dll;
    dll.head = NULL;
    dll.tail = NULL;
    return dll;
}

i2 dll_empty(Dll* dll)
{
    return dll->head == NULL;
}

void dll_append(Dll* dll, Node* n)
{
    if (dll->head == NULL) {
        dll->head = dll->tail = n;
        n->next = n->prev = NULL;
    } else {
        n->prev = dll->tail;
        n->next = NULL;
        dll->tail = dll->tail->next = n;
    }
}

void dll_remove(Dll* dll, Node* n)
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
