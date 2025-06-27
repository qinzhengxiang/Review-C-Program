#include "../include/DynamicArray.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




// 1. 内存管理
DynamicArray *CreateArr(size_t elem_size,size_t initCapacity){
    DynamicArray *arr = (DynamicArray *)malloc(sizeof(DynamicArray));
    arr->capacity = initCapacity;
    arr->size = 0;
    arr->elem_size = elem_size;
    arr->data = malloc(arr->capacity*arr->elem_size);

    return arr;
}
void DestoryArr(DynamicArray *arr){
    if(arr == NULL)return;

    free(arr->data);
    free(arr);
}

void reSize(DynamicArray *arr){
    arr->capacity *= 2;
    arr->data = realloc(arr->data, arr->capacity*arr->elem_size);
    if(!arr->data){
        perror("realloc failed");
        exit(EXIT_FAILURE);
    }
}

// 2. 数组功能函数
void push_back(DynamicArray *arr,void *val){
    if(arr->size >= arr->capacity){
        reSize(arr);
    }
    //计算目标内存地址，并拷贝数据
    void *tarSpace = (char *)arr->data + arr->size * arr->elem_size;
    memcpy(tarSpace, val,arr->elem_size);
    arr->size++;
}


void pop(DynamicArray *arr){
    erase(arr, arr->size-1);
}


void insert(DynamicArray *arr,size_t index,void *val){
    if(index > arr->size)return ;
    if(index == arr->size){
        push_back(arr, val);
        return ;
    }
    if(arr->size >= arr->capacity){
        reSize(arr);
    }


    void *temp = malloc(arr->elem_size*(arr->size - index));
    void *tarIndex = (char *)arr->data + arr->size * index;
    memcpy(temp, tarIndex, arr->elem_size*(arr->size-index));

    memcpy(tarIndex, val, arr->elem_size);

    tarIndex += arr->elem_size;
    memcpy(tarIndex, temp, arr->elem_size*(arr->size - index));

    arr->size++;
}

void erase(DynamicArray *arr,size_t index){
    if(index >=arr->size)return;
    void *tarSpace = (char *)arr->data + arr->elem_size * (index);

    memcpy(tarSpace, tarSpace + arr->elem_size, arr->elem_size * (arr->size - index));
    arr->size--;
}


void *at(DynamicArray *arr,size_t index){
    if(index >= arr->size){
        fprintf(stderr, "Index out of bounds!\n");
        return NULL;
    }
    //计算元素地址：起始地址 + 索引 * 元素大小
    return (char *)arr->data + index*arr->elem_size;
}




// 3. 其余函数
size_t size(DynamicArray *arr){
    return arr->size;
}
bool  empty(DynamicArray *arr){
    return (arr->size == 0);
}

//清空元素--保留内存
void clear(DynamicArray *arr){
    arr->size = 0;
}
