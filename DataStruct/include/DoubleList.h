#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include <stdlib.h>

struct ListNode;

typedef struct ListNode{
    struct ListNode *next;
    struct ListNode *prev;
    void *value;
}ListNode;


typedef struct List{
    ListNode *Head;
    ListNode *Tail;
}List;


List* ListCreate();
void ListDestory(List* list);

void ListAppend(List* list,void* val);
void ListPrepend(List* list,void* val);
void RemoveHead(List* list);
void RemoveTail(List* list);

ListNode *ListFind(List *list, void *value, int (*compare)(void *, void *));
ListNode *ListGetNodeAt(List* list,int index);
ListNode *ListGetHead(List *list);
ListNode *ListGetTail(List *list);

void ListTraverseForward(List *list, void (*func)(void *));
void ListTraverseBackward(List *list, void (*func)(void *));


#endif