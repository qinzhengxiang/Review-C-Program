#include "../include/DoubleList.h"

#include <stdlib.h>


List* ListCreate(){
    List* list = malloc(sizeof(List));
    if(list == NULL)return NULL;

    list->Head = (ListNode *)malloc(sizeof(ListNode));
    list->Tail = (ListNode *)malloc(sizeof(ListNode));


    list->Head->prev = NULL;
    list->Head->next = list->Tail;
    list->Tail->prev = list->Head;
    list->Tail->next = NULL;

    return list;
}

//析构函数中，优先free最底层结构，然后在释放上层结构
void ListDestory(List* list){
    if(list == NULL)return;

    ListNode* cur = list->Head;
    while(cur){
        ListNode* next = cur->next;
        free(cur);
        cur = next;
    }
    free(list);
}

//头部插入
void ListPrepend(List* list,void* val){
    ListNode* newNode = malloc(sizeof(ListNode));
    newNode->value = val;

    ListNode *he = list->Head->next;

    list->Head->next = newNode;
    newNode->prev = list->Head;

    newNode->next = he;
    he->prev = newNode;
}

void ListAppend(List* list,void* val){
    ListNode* newNode = malloc(sizeof(ListNode));
    newNode->value = val;

    ListNode* pr = list->Tail->prev;
    
    pr->next = newNode;
    newNode->prev = pr;

    newNode->next = list->Tail;
    list->Tail->prev = newNode;
}

//去除头节点
void RemoveHead(List* list){
    if(list->Head->next == NULL)return;

    ListNode* re = list->Head->next;
    list->Head->next = re->next;
    re->next->prev = list->Head;

    free(re);
}


void RemoveTail(List* list){
    if(list->Tail == NULL)return;

    ListNode* re = list->Tail->prev;
    list->Tail->prev = re->prev;
    re->prev->next = list->Tail;

    free(re);
}


ListNode *ListFind(List *list, void *value, int (*compare)(void *, void *)){
    if(!list || !compare)return NULL;
    ListNode* cur = list->Head->next;

    while(cur){
        if(compare(value,cur->value))return cur;
        cur = cur->next;
    }
    return NULL;
}


ListNode* ListGetNodeAt(List* list,int index){
    if(!list)return NULL;
    int _index = 0;

    ListNode* cur = list->Head->next;
    while (cur) {
        if(_index == index)return cur;
        cur = cur->next;
        _index++;
    }
    return NULL;
}
ListNode *ListGetHead(List *list){
    if(!list)return NULL;
    
    return (list->Head->next);
}
ListNode *ListGetTail(List *list){
    if(!list)return NULL;

    return (list->Tail->prev);
}


void ListTraverseForward(List *list, void (*func)(void *)){
    if(!list || !func)return;

    ListNode* cur = list->Head->next;
    while(cur != list->Tail){
        func(cur->value);
        cur = cur->next;
    }
}

void ListTraverseBackward(List *list, void (*func)(void *)){
    if(!list || !func)return;
    
    ListNode* cur = list->Tail->prev;
    while(cur != list->Head){
        func(cur->value);
        cur = cur->prev;
    }
}