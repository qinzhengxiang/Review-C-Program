#include "Stack.h"
#include "DoubleList.h"
#include <stdlib.h>


List *Stack_Create(){
    return ListCreate();
}
void Stack_Destory(List *list){
    ListDestory(list);
    return ;
}

void StackPush(List *list,void *val){
    ListPrepend(list,val);
}
void StackPop(List *list){
    RemoveHead(list);
}
void *StackTop(List *list){
    return (ListGetHead(list));
}
size_t StackSize(List *list){
    size_t count = 0;
    ListNode *cur = list->Head->next;
    while(cur){
        cur = cur->next;
        count++;
    }
    return count;
}
bool StackEmpty(List *list){
    return (list->Head->next == list->Tail->prev);
}