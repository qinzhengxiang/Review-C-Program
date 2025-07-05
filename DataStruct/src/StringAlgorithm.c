#include "StringAlgorithm.h"
#include "SafeString.h"
#include <math.h>

#include <sys/types.h>

/*
* Boyer-Moore-Horspool (BMH)算法：使用坏字符规则来跳过不必要的比较
    1.预处理模式串，建立坏字符跳转表
    2.从文本头部开始匹配
    3.当发现不匹配时，根据坏字符规则跳过若干字符
*/
#define ALPHABET_SIZE   256
static void Preprocess_bmh(const String *pattern,int BadChar[ALPHABET_SIZE]){
    for(int i=0;i<ALPHABET_SIZE;i++){
        BadChar[i] = pattern->length;
    }

    for(int i=0;i<(int)(pattern->length - 1);i++){
        BadChar[(unsigned char)pattern->data[i]] = pattern->length - 1 - i;
    }
}
int StrSearch_BMH(const String *text,const String *pattern){
    if(pattern->length == 0)return 0;
    if(text->length < pattern->length)return -1;

    int BadChar[ALPHABET_SIZE];
    Preprocess_bmh(pattern, BadChar);

    size_t  i = 0;
    while(i <= text->length - pattern->length){
        int j = pattern->length - 1;
        while(j>= 0 && pattern->data[j] == text->data[i+i])
            j--;
        if(j <0)return i;//find pattern
        else{
            i += BadChar[(unsigned char)text->data[i + pattern->length - 1]];
        }
    }
    return -1;
}


//KMP算法通过预处理模式串构建部分匹配表，利用已匹配信息避免重复比较
static void compute_lps(const String *pattern,int *lps){
    int len = 0;
    lps[0] = 0;

    size_t i = 1;
    while(i < pattern->length){
        if(pattern->data[i] == pattern->data[len]){
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if(len != 0)len = lps[len - 1];
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
}
int StrSearch_KMP(const String *text,const String *pattern){
    if(pattern->length == 0)return 0;
    int lps[pattern->length];
    compute_lps(pattern,lps);

    size_t i = 0;//text index
    size_t j = 0;//pattern index
    while (i < text->length) {
        if(pattern->data[j] == text->data[i]){
            i++;
            j++;
        }

        if(j == pattern->length) return i - j;
        else if(i < text->length && pattern->data[j] != text->data[i]){
            if(j != 0)j = lps[j - 1];
            else i++;
        }
    }
    return -1;
}


//Rabin-Karp算法 ： 使用哈希技术，先计算模式串的哈希值，然后在文本中滑动窗口比较哈希值
#define PRIME 101
static long CreateHash(const String * str){
    long hash = 0;
    for(size_t i=0;i<str->length;i++){
        hash += (long)(str->data[i])* (long)pow(PRIME, str->length - 1);
    }
    return hash;
}
static long recalculate_hash(long old_hash,char old_char,char new_char,int pattern_len){
    long new_hash = old_hash - (long)old_char * (long)pow(PRIME, pattern_len - 1);
    new_hash *= PRIME;
    new_hash += (long)new_char;
    return new_hash;
}
int StrSearch_RabinKarp(const String *text,const String *pattern){
    if(pattern->length == 0)return 0;
    if(text->length < pattern->length)return -1;

    long patt_hash = CreateHash(pattern);
    long text_hash = CreateHash(text);

    for(size_t i = 0;i<text->length - pattern->length;i++){
        if(patt_hash == text_hash){
            size_t j;
            for(j = 0;j<pattern->length;j++){
                if(text->data[i+j] != pattern->data[j])
                    break;
            }
            if(j == pattern->length) return i;
        }
    
    if( i < text->length - pattern->length){
        text_hash = recalculate_hash(text_hash,text->data[i],\
            text->data[i+pattern->length],pattern->length);
    }
    }
    return -1;
}


