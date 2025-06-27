#include "../include/DoubleList.h"
#include <stddef.h>
#include <stdio.h>

void ListPrint(void *val){
    printf("This node val = %d\n",*(int*)val);
}

int compare(void *a,void *b){
    int *num1 = (int *)a;
    int *num2 = (int *)b;
    if(labs(num1-num2) < 2)return 0;
    return -1;
}

int main(){
    printf("This Process is %d\n",0);
    List* list = ListCreate();

    int arr[5] = {0,1,2,3,4};
    printf("This Process is %d\n",1);
    for(int i=0;i<5;i++){
        ListAppend(list,&arr[i]);
    }

    printf("This Process is %d\n",2);
    ListTraverseBackward(list,ListPrint);
    RemoveHead(list);
    RemoveTail(list);
    printf("This Process is %d\n",3);
    ListTraverseBackward(list,ListPrint);

    int c = 10;
    ListNode* finNode = ListFind(list,&c,compare);
    if(finNode != NULL)printf("Find Node Val =  %d\n",*(int *)finNode->value);
    ListDestory(list);
    //ListTraverseBackward(list,ListPrint);
    printf("This Process is %d\n",4);
    return 0;
}