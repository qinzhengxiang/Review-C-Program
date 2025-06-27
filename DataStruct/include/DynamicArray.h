#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

#define initSize    10

typedef struct{
  void      *data;      //指向动态分配的内存块---存储实际数据
  size_t    size;       //当前元素个数
  size_t    capacity;   //当前总容量
  size_t    elem_size;  //每个元素的大小（字节数，支持泛型）
}DynamicArray;



// 1. 内存管理
DynamicArray *CreateArr(size_t elem_size,size_t initCapacity);
void DestoryArr(DynamicArray *arr);


// 2. 数组功能函数
void push_back(DynamicArray *arr,void *val);
void pop(DynamicArray *arr);
void insert(DynamicArray *arr,size_t index,void *val);
void erase(DynamicArray *arr,size_t index);
void *at(DynamicArray *arr,size_t index);


// 3. 其余函数
size_t size(DynamicArray *arr);
bool  empty(DynamicArray *arr);
void clear(DynamicArray *arr);//清空元素--保留内存




#endif