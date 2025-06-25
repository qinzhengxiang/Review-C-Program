#ifndef __PRINTF
#define __PRINTF

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>


/*颜色定义*/
#define COLOR_RESET     "\033[0m"
#define COLOR_RED       "\033[31m"
#define COLOR_GREEN     "\033[32m"
#define COLOR_YELLOW    "\033[33m"
#define COLOR_BLUE      "\033[34m"
#define COLOR_MAGENTA   "\033[35m"
#define COLOR_CYAN      "\033[36m"
#define COLOR_WHITE     "\033[37m"


/* 获取当前时间字符串 */
#define __CURRENT_TIME__ \
     ({ \
       time_t __t = time(NULL); \
        struct tm *__tm = localtime(&__t); \
        static char __buf[26]; \
        strftime(__buf, sizeof(__buf),"%Y-%m-%d %H:%M:%S", __tm); \
        __buf; \
    })

/* 获取文件名（不含路径） */
#define __SHORT_FILE__ (strrchr(__FILE__,'/') ? strrchr(__FILE__,'/') + 1 : __FILE__)

/* 自定义颜色打印宏 - 基础实现 */
#define PRINT_COLOR(color, level, fmt, ...) \
    do { \
        printf("%s%s[%s] %s:%d [%s] " fmt COLOR_RESET"\n", \
        color, __CURRENT_TIME__, level, __SHORT_FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    } while(0)


/* 彩色打印宏 */
/* 彩色打印宏 - 复用基础宏 */
#define PRINT(fmt, ...)         PRINT_COLOR(COLOR_WHITE,  "INFO", fmt, ##__VA_ARGS__)
#define PRINT_RED(fmt, ...)     PRINT_COLOR(COLOR_RED,    "ERRO", fmt, ##__VA_ARGS__)
#define PRINT_GREEN(fmt, ...)   PRINT_COLOR(COLOR_GREEN,  "INFO", fmt, ##__VA_ARGS__)
#define PRINT_YELLOW(fmt, ...)  PRINT_COLOR(COLOR_YELLOW, "WARN", fmt, ##__VA_ARGS__)
#define PRINT_BLUE(fmt, ...)    PRINT_COLOR(COLOR_BLUE,   "INFO", fmt, ##__VA_ARGS__)
#define PRINT_MAGENTA(fmt, ...) PRINT_COLOR(COLOR_MAGENTA,"INFO", fmt, ##__VA_ARGS__)
#define PRINT_CYAN(fmt, ...)    PRINT_COLOR(COLOR_CYAN,   "INFO", fmt, ##__VA_ARGS__)
#define PRINT_WHITE(fmt, ...)   PRINT_COLOR(COLOR_WHITE,  "INFO", fmt, ##__VA_ARGS__)

/*  C语言：可变参数定义
    ... 表示可变参数部分，可以是0个至多个
    ##__VA_ARGS__   C预处理器定义的特殊标识符，代表宏调用时传递的可变参数列表

*/

#endif