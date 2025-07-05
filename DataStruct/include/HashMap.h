/*
* use Dynamic Array and LinkList Struct to solve HashMap
*/

#ifndef HASH_MAP_
#define HASH_MAP_

#include <stdlib.h>

#define LOAD_FACTOR_THRESHOLD 0.75

typedef struct HashNode{
    void *key;
    void *value;
    struct HashNode *next;//链表指针
}HashNode;


typedef struct{
    HashNode** buckets; //动态数组存储链表头指针
    size_t capacity;    //数组当前容量
    size_t size;        //键值对总数

    size_t (*HashFunc)(void* key);  //哈希函数
    int (*KeyCmp)(void *key1,void *key2);   //键比较函数
}HashTable;




HashTable *HashCreate(size_t capacity);

void HashTableInsert(HashTable *table,void *key,void *value);

void* HashTableGet(HashTable *table,void *key);

void HashTableRemove(HashTable *table,void *key);



void HashTableDestory(HashTable *table);

#endif