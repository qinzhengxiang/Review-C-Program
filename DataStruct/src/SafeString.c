#include"../include/SafeString.h"




String *StringCreate(){
    
}

String *StringFromC(const char *cstr);

void StringDestory(String *str);

void StringAppendChar(String *str,char c);
void StringAppendCstr(String *str,const char *cstr);

const char *String2cstr(const String *str);

String *StringCopy(const String *src);

int StringEquals(const String *a,const String *b);//字符串比较