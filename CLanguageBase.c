/*
**  指针数组  VS  数组指针
**  指针数组是装指针的盒子，数组指针是指向盒子的手
*/
#include <stdio.h>

void ArrPtr(){
    //指针数组：是个数组，里面装的都是指针
    char *arr1[] = {"Apple","Banana","Orange"};

    //数组指针：是个指针，指向一个数组
    int nums[] = {1,2,3,4,5};
    int (*arr2)[5] = &nums;

    printf("指针数组的内容：\n");
    for(int i=0;i<3;i++){
        printf("%s  ",arr1[i]);
    }
    printf("\n");


    printf("数组指针指向的数组：\n");
    for(int i=0;i<5;i++){
        printf("%d",(*arr2)[i]);
    }
    printf("\n");
}


/*
**  void指针---> 万能胶水       使用void指针的时候，需要显示声明类型
*/
void voidFun(){
    int num = 100;
    float pi = 3.14;
    char ch = 'A';

    void *magic_ptr;    //万能指针

    magic_ptr = &num;
    printf("指向整数：%d\n",*(int*)magic_ptr);

    magic_ptr = &pi;
    printf("指向小数：%.2f\n",*(float*)magic_ptr);

    magic_ptr = &ch;
    printf("指向字符：%c\n",*(char*)magic_ptr);

}



/*
**  指针数组做函数跳转表
*/
float add(float a,float b) { return a + b; }
float sub(float a,float b) { return a - b; }
float mul(float a,float b) { return a * b; }
float div(float a,float b) { return a / b; }

void FunPtr() {
    float (*calc[])(float,float) = {add, sub, mul, div};
    char ops[] = {'+','-','*','/'};

    float a = 10, b = 3;

    printf("简易计算器演示：\n");
    for(int i = 0; i < 4; i++) {
    printf("%.1f %c %.1f = %.2f\n", a, ops[i], b, calc[i](a, b));
    }
}



/*
**  const指针的三种姿势：   顶层const定内容，底层const定指向
*/
void constPtr(){
    int a = 10,b = 20;


    //S1:指向常量的指针（指针指向可变，内容不可变）
    const int *p1 = &a;
    printf("p1指向:%d\n",*p1);      //10
    p1 = &b;    //可以改指向
    printf("p1现在指向:%d\n",*p1);  //20
    // *p1 = 30 这个会报错，不能修改内容


    //S2:常量指针（指针指向不可变，内容可变）
    int *const p2 = &a;
    *p2 = 30;   //可以修改内容
    //p2 = &b 这个会报错，不能改指向


    //S3:指向常量的常量指针（指向和内容都不能变）
    const int * const p3 = &a;
    // *p3 = 40; 报错
    // p3 = &b; 报错

}


/*
**  指针与内存：
*/
#include <stdio.h>
#include <stdlib.h>

void DynamicSpace(){
    int size = 10;
    int *arr = (int*)malloc(size*sizeof(int));
    for(int i=0;i<size;i++)arr[i] = (i+1)*10;   //填充数据
    free(arr);
}

void Space4Ptr(){//指针生成二维数组
    int rows = 3,cols = 4;

    //分配指针数组
    int **matrix = (int **)malloc(rows * sizeof(int*));

    //为每一行分配空间
    for(int i=0;i<rows;i++){
        matrix[i] = (int*)malloc(cols*sizeof(int));
    }

    //填充数据
    int count = 1;
    for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
         matrix[i][j] = count++;
        }
    }

    //释放空间
    for(int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


/*
**  回调函数
*/
void sayHello(){
    printf("你好！\n");
}

void sayBye(){
    printf("再见！\n");
}

void greet(void (*callback)()){
    printf("准备打招呼...\n");
    callback();  // 调用传进来的函数
    printf("招呼打完了！\n");
}
int CallFun(){
    printf("=== 回调函数演示 ===\n");
    greet(sayHello);
    printf("\n");
    greet(sayBye);
}


/*
**  typedef and  ptr
*/
typedef int (*MathFunc)(int, int);
typedef int** IntPtrPtr;

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

void fun(){
    //使用简化的类型名
    MathFunc operations[] = {add, mul};
    printf("加法：%d\n", operations[0](5, 3));  // 输出：8
    printf("乘法：%d\n", operations[1](5, 3));  // 输出：15

    //二级指针的简化使用
    int num = 100;
    int *p1 = &num;     // p1是指向num的指针
    IntPtrPtr p2 = &p1; // p2是指向p1的指针

    printf("通过二级指针访问：%d\n", **p2);  // 输出：100
}