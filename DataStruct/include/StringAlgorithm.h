#ifndef String_Algorithm_H
#define String_Algorithm_H

#include "SafeString.h"
#include <stdint.h>
//1. 以下是常见的快速字符串搜索算法
int StrSearch_BMH(const String *text,const String *pattern);
int StrSearch_KMP(const String *text,const String *pattern);
int StrSearch_RabinKarp(const String *text,const String *pattern);

//2. 字符串转换与编码
// 在String结构中增加编码类型字段
typedef enum { ENC_ASCII, ENC_UTF8, ENC_GBK } StringEncoding;

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
    StringEncoding encoding;
} StringCode;

int StringConvertEncoding(String *str, StringEncoding new_encoding);

    //大小写转换
void StringToLower(String *str);
void StringToUpper(String *str);
    //URL编码、解码
String *StringURLEncode(const String *str);
String *StringURLDecode(const String *str);

// 3. 字符串分拆与组合
    //分词处理
typedef struct {
    String *tokens;
    size_t count;
} StringTokens;

StringTokens StringSplit(const String *str, const String *delimiter);
void StringTokensFree(StringTokens *tokens);

    //正则表达式
typedef struct {
    // 正则表达式编译后的状态
    void *compiled_pattern;
} StringRegex;

StringRegex *StringRegexCompile(const String *pattern);
void  StringRegexMatch(const StringRegex *regex, const String *text);

// 4. 字符串分析与度量
    //哈希算法
uint64_t StringHashFNV1a(const String *str);
uint64_t StringHashDJB2(const String *str);
    //相似度计算
double StringSimilarityLevenshtein(const String *a, const String *b);
double StringSimilarityJaccard(const String *a, const String *b);
    //统计分析
typedef struct {
    char character;
    size_t count;
} CharFrequency;

CharFrequency *StringCharacterFrequency(const String *str);


// 5. 字符串压缩与加密
    //简单压缩
String *StringCompressRLE(const String *str); // 游程编码
String *StringDecompressRLE(const String *compressed);
    //基础加密
String *StringXORCipher(const String *str, const String *key);

// 6. 高级字符串结构
    //Tire Tree
typedef struct StringTrieNode {
    struct StringTrieNode *children[256];
    bool is_end_of_word;
} StringTrie;

void StringTrieInsert(StringTrie *trie, const String *word);
bool StringTrieSearch(const StringTrie *trie, const String *word);

    //后缀自动机
typedef struct {
    // 后缀自动机状态表示
} StringSuffixAutomaton;

StringSuffixAutomaton *StringBuildSuffixAutomaton(const String *str);
// 7. 实用工具函数 
    //格式化处理
String *StringFormat(const char *format, ...);
    //空白处理
void StringTrimLeft(String *str);
void StringTrimRight(String *str);
void StringTrim(String *str);
    //填充与对齐
void StringPadLeft(String *str, size_t length, char pad_char);
void StringPadRight(String *str, size_t length, char pad_char);
//


#endif