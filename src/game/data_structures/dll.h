#ifndef DLL_H
#define DLL_H

#include <gvec.h>
#include <gtype.h>

typedef struct DLLNode DLLNode;

typedef struct Data {
    void* obj;
    DLLNode* node;
} Data;

typedef struct DLLNode {
    Data* data;
    struct DLLNode* next;
    struct DLLNode* prev;
} DLLNode;

typedef struct DLL {
    struct DLLNode* head;
} DLL;

Data* data_create(void* obj);
void data_destroy(Data* d);

DLLNode* dll_node_create(Data* d);

DLL dll_create(void);
i2 dll_empty(DLL* dll);
void dll_push(DLL* dll, DLLNode* n);
void dll_remove(DLL* dll, DLLNode* n);

#endif