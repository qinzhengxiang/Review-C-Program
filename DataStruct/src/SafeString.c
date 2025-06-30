#include"../include/SafeString.h"


#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


String *StringCreate(){
    String *str = (String *)malloc(sizeof(String));

    str->data = malloc(1);
    str->data[0] = '\0';
    str->length = 0;
    str->capacity = 1;

    return str;
}


void StringDestory(String *str){
    free(str->data);
    free(str);
}



void StringAppendChar(String *str,char c){
    if(str->length+1 >= str->capacity){
        str->capacity *= 2;
        str->data = realloc(str->data, str->capacity);
    }
    str->data[str->length++] = c;
    str->data[str->length] = '\0';
}



void StringAppendCstr(String *str,const char *cstr){
    size_t len = strlen(cstr);
    if(str->length + len + 1 > str->capacity){
        while(str->length + len + 1 > str->capacity){
            str->capacity *= 2;
        }
        str->data = realloc(str->data, str->capacity);
    }

    memcpy(str->data + str->length, cstr, len + 1);
    str->length += len;
}

String *StringFromC(const char *cstr){
    size_t len = strlen(cstr);

    String *str = (String *)malloc(sizeof(String));
    str->data = malloc(sizeof(len+1));
    str->length = len;
    str->capacity = len + 1;

    memcpy(str->data, cstr, str->capacity);
    
    return str;
}


const char *String2cstr(const String *str){
    char *cstr = malloc(sizeof(str->length));

    memcpy(cstr,str->data, str->length);

    return cstr;
}



String *StringCopy(const String *str){
    String *tar = malloc(sizeof(String));

    tar->data = malloc(str->capacity);

    memcpy(tar->data,str->data, str->length);

    tar->capacity = str->capacity;
    tar->length = str->length;

    return tar;
}


//字符串比较
int StringEquals(const String *a,const String *b){
    if(a->length > b->length)return 1;
    else if(a->length < b->length)return -1;

    size_t index = 0;
    while(a->data[index] == b->data[index] && index < a->length){
        index++;
    }

    if(index == a->length)return 0;
    return -2;
}


void StringPrint(const char *introduce,String *str){
    char *_data = str->data;
    printf("%s  ",introduce);
    for(size_t i=0;i<str->length;i++){
        printf("%c",*_data);
        _data++;
    }
    printf("\n");
}


void StringPopback(String *str){
    str->data = realloc(str->data, str->length - 1);
    str->length--;
}

void StringErase(String *str,size_t index){
    if(index >= str->length)return ;

    char *ptr = str->data + index;
    memcpy(ptr,ptr+1, str->length - index);
    str->length--;

}
void StringInsert(String* str,size_t index,const char c){
    if(index >= str->length){
        StringAppendChar(str, c);
        return;
    }

    char *temp = malloc(sizeof(char)*(str->length - index));
    char *tarIndex = (char *)str->data + index;
    memcpy(temp,tarIndex, (str->length - index)*sizeof(char));
    memcpy(tarIndex,&c, sizeof(char));
    memcpy(tarIndex+sizeof(char), temp, sizeof(char)*(str->length - index));

    free(temp);
    str->length++;
}
void StringChange(String *str,size_t index,const char c){
    memcpy(str->data + sizeof(char)*index, &c, sizeof(char));
}
int StringFind(String *str,const char c){
    size_t index;
    for(index = 0;index < str->length;index++){
       if(memcmp(&str->data[index], &c, sizeof(char)) == 0)return index;
    }
    return -1;
}


char StringAt(String *str,size_t index){
    if(!str || !str->data ||index >= str->length)return '\0';

    return (char)(str->data[index]);
}