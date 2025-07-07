#ifndef STACK_H
#define STACK_H

#include "DoubleList.h"
#include <stdlib.h>
#include <stdbool.h>


List *Stack_Create();
void Stack_Destory(List *list);


void StackPush(List *list,void *val);
void StackPop(List *list);
void *StackTop(List *list);
size_t StackSize(List *list);
bool StackEmpty(List *list);


#endif