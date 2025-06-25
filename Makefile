# 定义编译器
CC = gcc

# 定义编译选项
CFLAGS = -Wall -g

# 定义目标可执行文件
TARGET = runProgram

# 定义源文件
SRCS = print4Embedned.c

# 定义对象文件 (由源文件自动生成)
OBJS = $(SRCS:.c=.o)

# 默认目标
all: $(TARGET)

# 链接目标
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 编译规则
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)
	
# Make run
run:$(TARGET)
	./$(TARGET)
	
