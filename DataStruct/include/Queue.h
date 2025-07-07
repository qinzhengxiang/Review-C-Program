#ifndef QUEUE_H
#define QUEUE_H

#include "DoubleList.h"
#include <stdlib.h>
#include <stdbool.h>

List *Queue_Create();
void Queue_Destory(List *list);

ListNode *QueueFront(List *list);
ListNode *QueueBack(List *list);

void QueuePush(List* list,void *val);
void QueuePop(List* list);

bool QueueEmpty(List *list);
size_t QueueSize(List *list);



#endif