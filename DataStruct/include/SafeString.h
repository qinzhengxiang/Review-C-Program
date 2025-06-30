#ifndef SAFE_STRING_
#define SAFE_STRING_

//构建更加安全的字符类型，类似C++的string  ||  string_view

#include <stddef.h>
#include <stdbool.h>

typedef struct{
    char *data;     //指向实际字符串内容
    size_t  length;   //当前有效长度
    size_t  capacity;//分配内存大小
}String;


String *StringCreate();

String *StringFromC(const char *cstr);

void StringDestory(String *str);

void StringAppendChar(String *str,char c);
void StringAppendCstr(String *str,const char *cstr);

const char *String2cstr(const String *str);

String *StringCopy(const String *str);

int StringEquals(const String *a,const String *b);//字符串比较

void StringPrint(const char *introduce,String *str);

void StringPopback(String *str);
void StringErase(String *str,size_t index);
void StringInsert(String* str,size_t index,const char c);
void StringChange(String *str,size_t index,const char c);
int  StringFind(String *str,const char c);
char StringAt(String *str,size_t index);



#endif