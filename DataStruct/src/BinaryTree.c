#include "BinaryTree.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//默认内存分配器
static void *default_alloc(size_t size){return malloc(size);}
static void default_free(void *ptr){free(ptr);}

static BSTreeNode *node_new(BSTree *tree,void *key,void *value,BSTreeNode *parent){
    BSTreeNode *node = tree->AllocFunc(sizeof(BSTreeNode));
    if(!node)return NULL;

    node->key = key;
    node->value = value;
    node->left = node->right = NULL;
    node->parent = parent;
    node->height = 1;

    return node;
}

static void node_free(BSTree *tree,BSTreeNode *node){
    if(tree->ValueFreeFunc && node->value){
        tree->ValueFreeFunc(node->value);
    }
    if(tree->KeyFreeFunc && node->key){
        tree->KeyFreeFunc(node->key);
    }
    tree->FreeFunc(node);
}

static int node_height(BSTreeNode *node){
    return node ? node->height : 0;
}

static void node_update_height(BSTreeNode *node){
    int left_height = node_height(node->left);
    int right_height = node_height(node->right);
    node->height = 1 + (left_height >= right_height ? left_height : right_height);
}


BSTree *BSTree_Create(BSTreeCompareFunc compare_func){
    return BSTree_CreateFull(
        default_alloc,
        compare_func,
        NULL,
        NULL,
        default_free
    );
}
BSTree *BSTree_CreateFull(
    BSTreeAllocFunc allocFun,
    BSTreeCompareFunc compare,
    BSTreeKeyFreeFunc keyFree,
    BSTreeValueFreeFunc valFree,
    BSTreeFreeFunc      freeFunc
){
    BSTree *tree = allocFun(sizeof(BSTree));
    if(!tree)return NULL;

    tree->root = NULL;
    tree->count = 0;
    tree->CompareFunc = compare;
    tree->KeyFreeFunc = keyFree;
    tree->ValueFreeFunc = valFree;
    tree->AllocFunc = allocFun ? allocFun : default_alloc;
    tree->FreeFunc = freeFunc ? freeFunc : default_free;
    tree->lock = NULL;

    return tree;
}

static void Tree_Destory_Recursive(BSTree *tree,BSTreeNode *node){
    if(!node) return ;

    Tree_Destory_Recursive(tree, node->left);
    Tree_Destory_Recursive(tree, node->right);
    node_free(tree, node);
}

void BSTree_Destory(BSTree *tree){
    if(!tree)return ;

    Tree_Destory_Recursive(tree, tree->root);
    tree->FreeFunc(tree);
}




//base operator

static BSTreeNode *tree_insert_recursive(
    BSTree *tree,
    BSTreeNode *node,
    void *key,
    void *value,
    BSTreeNode *parent,
    bool *inserted
){
    if(!node){
        *inserted = true;
        return node_new(tree, key, value, parent);
    }

    int cmp  = tree->CompareFunc(key,node->key);
    if(cmp < 0){
        node->left = tree_insert_recursive(tree, node->left,key,value, node, inserted);
    }else if(cmp > 0){
        node->right = tree_insert_recursive(tree, node->right,key,value, node, inserted);
    }else{
        //键值已存在，更新键对应的值
        if(tree->ValueFreeFunc && node->value){
            tree->ValueFreeFunc(node->value);
        }
        node->value = value;
        *inserted = false;
    }

    //更新树高-》为平衡树做准备
    node_update_height(node);
    return node;
}


bool BSTree_Insert(BSTree *tree,void *key,void *val){
    if(!tree || !key)return false;

    bool inserted = false;
    tree->root = tree_insert_recursive(tree,tree->root,key,val,NULL, &inserted);
    if(inserted)tree->count++;
    return inserted;
}

//  查找最小节点
static BSTreeNode *tree_find_min(BSTreeNode *node){
    while(node && node->left){
        node = node->left;
    }
    return node;
}

//删除节点--递归实现
static BSTreeNode *tree_remove_recursive(
    BSTree *tree,
    BSTreeNode  *node,
    const void *key,
    bool *removed,
    void **old_value
){
    if(!node){
        *removed = false;
        return NULL;
    }

    int cmp = tree->CompareFunc(key,node->key);
    if(cmp < 0){
        node->left = tree_remove_recursive(tree,node->left, key,removed, old_value);
    }else if(cmp > 0){
        node->right = tree_remove_recursive(tree,node->right, key,removed, old_value);
    }else{//找到要删除的节点
        *removed = true;
        *old_value = node->value;

        //case1:只有一个子节点或者没有子节点
        if(!node->left){
            BSTreeNode *temp = node->right;
            if(temp)temp->parent = node->parent;
            node_free(tree, node);
            return temp;
        }else if(!node->right){
            BSTreeNode *temp = node->left;
            if(temp)temp->parent = node->parent;
            node_free(tree, node);
            return temp;
        }


        //case2 :有两个子节点
        BSTreeNode *temp = tree_find_min(node->right);
        node->key = temp->key;
        node->value = temp->value;
        node->right = tree_remove_recursive(tree,node->right,key,removed, old_value);
    }

    if(node){
        node_update_height(node);
    }
    return node;
}

bool BSTree_Remove(BSTree *tree,const void *key){
    if(!tree || !key)return false;

    bool removed = false;
    void *old_value = NULL;
    tree->root = tree_remove_recursive(tree,tree->root,key,&removed,old_value);
    if(removed){
        tree->count--;
        if(tree->ValueFreeFunc && old_value){
            tree->ValueFreeFunc(old_value);
        }
    }
    return removed;
}


void *BSTree_Lookup(BSTree *tree,const void *key){
    if(!tree || !key)return NULL;

    BSTreeNode *node = tree->root;
    while(node){
        int cmp = tree->CompareFunc(key,node->key);
        if(cmp == 0)return node->value;
        else if(cmp < 0)node = node->left;
        else node = node->right;
    }
    return NULL;
}



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