#include "HashMap.h"

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static size_t HashFnv1a(void *key);
static size_t HashAdler32(void *key);
static size_t HashDjb(void *key);

const size_t FNV_PRIME = 16777619;
const size_t FNV_OFFSET_BASIS = 2166136261;

static  size_t HashString(void *key);    
static  int KeyCmpString(void *key1,void *key2);
static void HashTableResize(HashTable *table); 
static void HashMaybeResize(HashTable *table);

static size_t HashFnv1a(void *key){
    char *str = key;
    size_t hash = FNV_OFFSET_BASIS;
    size_t i = 0;

    for(i=0;i < strlen(str);i++){
        hash ^= str[i];
        hash *= FNV_PRIME;
    }

    return hash;
}

const size_t MOD_ADLER = 65521;
static size_t HashAdler32(void *key){
    char *str = key;
    size_t a = 1, b = 0;
    size_t i = 0;

    for(i = 0;i<strlen(str);i++){
        a = (a + str[i])%MOD_ADLER;
        b = (b + a)%MOD_ADLER;
    }

    return (b << 16) | a;
}


static size_t HashDjb(void *key){
    char *str = key;
    size_t hash = 5381;

    size_t i = 0;
    for(i=0;i<strlen(str);i++){
        hash = ((hash << 5 )+ hash) + str[i];
    }

    return hash;
}



//use djb2
static size_t HashString(void *key){
    char *str = (char *)key;
    size_t hash = 5381;
    int c;
    while((c = *str++)){
        hash = ((hash << 5) + hash) + c;
    }
    return c;
}


static int KeyCmpString(void *key1,void *key2){
    return strcmp((char *)key1, (char *)key2);
}


HashTable *HashCreate(size_t capacity){
    HashTable *table = malloc(sizeof(HashTable));
    table->capacity = capacity;
    table->size = 0;
    table->buckets = calloc(capacity, sizeof(HashNode*));
    table->HashFunc = HashString;
    
    if(0){//To resolve the Function unuse in Complier -Werror
        table->HashFunc = HashDjb;
        table->HashFunc = HashFnv1a;
        table->HashFunc = HashAdler32;
    }
    
    table->KeyCmp = KeyCmpString;
    return table;
}

void HashTableInsert(HashTable *table,void *key,void *value){
    HashMaybeResize(table);
    size_t index = table->HashFunc(key) % table->capacity;
    HashNode *node = table->buckets[index];

    while(node){
        if(table->KeyCmp(node->key,key) == 0){
            node->value = value;
            return ;
        }
        node = node->next;
    }

    HashNode *NewNode = malloc(sizeof(HashNode));
    NewNode->key = key;
    NewNode->value = value;
    NewNode->next = table->buckets[index];//头插法
    table->buckets[index] = NewNode;
    table->size++;
}

void* HashTableGet(HashTable *table,void *key){
    size_t index = table->HashFunc(key) % table->capacity;
    HashNode *node = table->buckets[index];
    while(node){
        if(table->KeyCmp(node->key,key) == 0)return node->value;
        node = node->next;
    }
    return NULL;
}

void HashTableRemove(HashTable *table,void *key){
    size_t index = table->HashFunc(key) % table->capacity;
    HashNode *node = table->buckets[index];
    HashNode *prev = NULL;

    while(node){
        if(table->KeyCmp(node->key,key) == 0){
            if(prev)prev->next = node->next;
            else table->buckets[index] = node->next;
            free(node);
            table->size--;
            return;
        }
        prev = node;
        node = node->next;
    }
}

void HashTableDestory(HashTable *table){
    for(size_t i=0;i<table->capacity;i++){
        HashNode *node = table->buckets[i];
        while(node){
            HashNode *tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(table->buckets);
    free(table);
}

static void HashTableResize(HashTable *table){
    size_t NewCapacity = table->capacity * 2;
    HashNode **NewBuckets = calloc(NewCapacity, sizeof(HashNode *));

    for(size_t i=0;i<table->capacity;i++){
        HashNode *node = table->buckets[i];
        while(node){
            HashNode *NeNode = node->next;

            size_t index = table->HashFunc(node->key) % NewCapacity;
            node->next = NewBuckets[index];
            NewBuckets[index] = node;
            node = NeNode;
        }
    }

    free(table->buckets);
    
    table->buckets = NewBuckets;
    table->capacity = NewCapacity;
}

static void HashMaybeResize(HashTable *table){
    if((double)table->size / table->capacity > LOAD_FACTOR_THRESHOLD){
        HashTableResize(table);
    }
}