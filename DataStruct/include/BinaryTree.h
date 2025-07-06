#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdbool.h>
#include <stddef.h>

typedef int (*BSTreeCompareFunc)(const void *key1,const void *key2);

//内存分配函数类型
typedef void* (*BSTreeAllocFunc)(size_t size);
typedef void  (*BSTreeFreeFunc)(void *ptr);

//键值释放函数类型
typedef void (*BSTreeKeyFreeFunc)(void *key);
typedef void (*BSTreeValueFreeFunc)(void *value);

//遍历回调函数
typedef bool (*BSTreeTraverseFunc)(void *key,void *value,void *user_data);


typedef struct BSTreeNode{
    void *key;
    void *value;

    struct BSTreeNode *left;
    struct BSTreeNode *right;
    struct BSTreeNode *parent;

    int height;//平衡信息 可以扩展为AVL或红黑树
    //可添加color 字段用于红黑树
}BSTreeNode;


typedef struct BSTree{
    BSTreeNode *root;
    size_t count;

    BSTreeCompareFunc CompareFunc;
    BSTreeKeyFreeFunc KeyFreeFunc;
    BSTreeValueFreeFunc ValueFreeFunc;

    BSTreeAllocFunc AllocFunc;
    BSTreeFreeFunc  FreeFunc;

    //线程安全相关
    void *lock; //通常为pthread_mutex_t 或 CRITCAL_SECTION
}BSTree;


//迭代器结构
typedef struct{
    BSTree *tree;
    BSTreeNode *cur;
    //用于非递归遍历的栈结构
    void *stack;
}BSTreeIterator;


BSTree *BSTree_Create(BSTreeCompareFunc compare_func);
BSTree *BSTree_CreateFull(
    BSTreeAllocFunc allocFun,
    BSTreeCompareFunc compare,
    BSTreeKeyFreeFunc keyFree,
    BSTreeValueFreeFunc valFree,
    BSTreeFreeFunc      freeFunc
);

void BSTree_Destory(BSTree *tree);

//base operator
bool BSTree_Insert(BSTree *tree,void *key,void *val);
bool BSTree_Remove(BSTree *tree,const void *key);
void *BSTree_Lookup(BSTree *tree,const void *key);
bool BSTree_Contains(BSTree *tree,const void *key);
size_t BSTree_Size(BSTree *tree);

//Iterator
void BSTree_Foreach(BSTree *tree,BSTreeTraverseFunc func,void *user_data);

BSTreeIterator *BSTree_Iterator_Create(BSTree *tree);
void BSTree_Iterator_Destory(BSTreeIterator *iter);
bool BSTree_Iterator_Next(BSTreeIterator *iter,void **key,void **value);

// 扩展功能
BSTreeNode *BSTree_first_node(BSTree *tree);
BSTreeNode *BSTree_last_node(BSTree *tree);
BSTreeNode *BSTree_node_next(BSTreeNode *node);
BSTreeNode *BSTree_node_previous(BSTreeNode *node);

// 线程安全版本(可选)
BSTree *bstree_new_synchronized(BSTreeCompareFunc compare_func);
void bstree_lock(BSTree *tree);
void bstree_unlock(BSTree *tree);

#endif