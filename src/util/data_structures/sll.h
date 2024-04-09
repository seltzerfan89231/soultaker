#ifndef SLL_H
#define SLL_H

typedef struct SLLNode {
    void* obj;
    struct SLLNode* next;
} SLLNode;

typedef struct SLL {
    struct SLLNode* head;
} SLL;

SLL sll_create(void);

#endif