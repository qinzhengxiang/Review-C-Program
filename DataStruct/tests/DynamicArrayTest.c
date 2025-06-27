#include "../include/DoubleList.h"
#include "../include/DynamicArray.h"

#include <stddef.h>
#include <stdio.h>



int main(){

    DynamicArray* darr = CreateArr(4,1);
    int arr[5] = {1,2,3,4,5};

    for(int i=0;i<5;i++){
        push_back(darr,&arr[i]);
    }

    printf("Dynamic Array element val = %d\n",*(int*)at(darr,0));
    erase(darr, 0);
    printf("Dynamic Array element val = %d\n",*(int*)at(darr,0));
    int val = 10;
    insert(darr,0,&val);
    printf("Dynamic Array element val = %d\n",*(int*)at(darr,0));

    printf("Dynamic Array size is %ld\n",size(darr));   
    clear(darr); 
    printf("Dynamic Array Capacity is %ld\n",darr->capacity);

    DestoryArr(darr);
    return 0;
}