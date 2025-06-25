#include "printf.h"

int main(){
    // 基本打印测试
    // 基本打印测试
    PRINT("打印测试");
        
    // 颜色打印测试
    PRINT_RED("红色/RED - 通常用于错误信息");
    PRINT_GREEN("绿色/GREEN - 通常用于成功信息");
    PRINT_YELLOW("黄色/YELLOW - 通常用于警告信息");
    PRINT_BLUE("蓝色/BLUE - 通常用于调试信息");
    PRINT_MAGENTA("洋红色/MAGENTA - 用于特殊标记");
    PRINT_CYAN("青色/CYAN - 用于信息提示");
    PRINT_WHITE("白色/WHITE - 用于普通输出");
    
    return 0;
}