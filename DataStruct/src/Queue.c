#include "Queue.h"
#include "DoubleList.h"
#include <stdlib.h>



List *Queue_Create(){
    return ListCreate();
}
void Queue_Destory(List *list){
    ListDestory(list);
}

ListNode *QueueFront(List *list){
    return ListGetTail(list);
}
ListNode *QueueBack(List *list){
    return ListGetHead(list);
}

void QueuePush(List* list,void *val){
    ListPrepend(list, val);
}
void QueuePop(List* list){
    RemoveTail(list);
}

bool QueueEmpty(List *list){
    return (list->Head->next == list->Tail->prev);
}
size_t QueueSize(List *list){
    ListNode *cur = list->Head->next;
    size_t count = 0;

    while(cur){
        cur = cur->next;
        count++;
    }
    return count;
}
