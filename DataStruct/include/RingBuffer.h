#ifndef Ring_Buffer_H
#define Ring_Buffer_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *buffer;    // 数据存储区
    size_t capacity;    // 缓冲区总容量
    size_t head;        // 写入位置(下一个空闲位置)
    size_t tail;        // 读取位置(最老的数据位置)
    bool full;          // 缓冲区是否已满标志
} RingBuffer;

// 初始化环形缓冲区
RingBuffer* ring_buffer_init(size_t size);

// 释放环形缓冲区
void ring_buffer_free(RingBuffer *rb);

// 重置环形缓冲区
void ring_buffer_reset(RingBuffer *rb);

// 向缓冲区写入数据
bool ring_buffer_push(RingBuffer *rb, uint8_t data);

// 从缓冲区读取数据
bool ring_buffer_pop(RingBuffer *rb, uint8_t *data);

// 查看但不移除下一个数据
bool ring_buffer_peek(const RingBuffer *rb, uint8_t *data);

// 缓冲区是否为空
bool ring_buffer_is_empty(const RingBuffer *rb);

// 缓冲区是否已满
bool ring_buffer_is_full(const RingBuffer *rb);

// 获取缓冲区可用空间
size_t ring_buffer_available(const RingBuffer *rb);

// 获取缓冲区已用空间
size_t ring_buffer_size(const RingBuffer *rb);

// 批量写入数据
size_t ring_buffer_write(RingBuffer *rb, const uint8_t *data, size_t len);

// 批量读取数据
size_t ring_buffer_read(RingBuffer *rb, uint8_t *data, size_t len);




#endif