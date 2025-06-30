#include "../include/DoubleList.h"
#include "../include/DynamicArray.h"
#include "../include/SafeString.h"

#include <stddef.h>
#include <stdio.h>



int main(){
    String * str = StringCreate();

    StringAppendChar(str,'A');
    char *s = "BBBBBB"; 
    StringAppendCstr(str,s);
    StringPopback(str);
    StringPrint("Append && Popback str :",str);
    StringErase(str,2);
    StringPrint("Erase str :",str);
    StringInsert(str,2,'C');
    StringPrint("insert str :",str);
    StringChange(str,3,'D');
    StringPrint("Change str :",str);
    printf("find str : %d\n", StringFind(str,'C'));
    printf("find str index : %c\n", StringAt(str,2));
    StringPrint("print StringPrint :",StringCopy(StringFromC(s)));
    
    const char * s2 = String2cstr(str);
    printf("s2 : %s\n",s2);
    printf("StringEquals s1 s2 biggest :%d \n",StringEquals(str,StringFromC(s)));

    StringDestory(str);
    return 0;
}