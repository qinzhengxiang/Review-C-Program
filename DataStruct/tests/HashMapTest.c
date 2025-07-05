#include "HashMap.h"

#include <stddef.h>
#include <stdio.h>



int main(){
    HashTable * table = HashCreate(1);
    HashTableInsert(table, "name","ZhengxiangQin");
    HashTableInsert(table,"age","26");
    HashTableInsert(table,"address","shanghai");
    HashTableInsert(table,"QQ","1838386698");
    HashTableInsert(table,"iphone","19821396139");
    HashTableInsert(table,"e-mail","qinzhengxiang@foxmail.com");
    HashTableInsert(table,"age","28");

    printf("HashTableGet value : %s\n",(char *)HashTableGet(table, "name"));
    printf("HashTableGet value : %s\n",(char *)HashTableGet(table, "age"));
    
    HashTableRemove(table,"age");
    printf("HashTableGet value : %s\n",(char *)HashTableGet(table, "QQ"));

    HashTableDestory(table);
    return 0;
}