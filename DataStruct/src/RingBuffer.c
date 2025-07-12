#include "RingBuffer.h"
#include <stdbool.h>
#include <stdlib.h>


// 初始化环形缓冲区
RingBuffer* ring_buffer_init(size_t size){
    RingBuffer *ring = malloc(sizeof(RingBuffer));
    ring->buffer = malloc(size*sizeof(ring->buffer));
    ring->capacity = size;
    ring->head = ring->tail = 0;
    ring->full = false;
    return ring;
}

// 释放环形缓冲区
void ring_buffer_free(RingBuffer *rb){
    if(rb->buffer){
        free(rb->buffer);
        rb->buffer = NULL;
    }
    if(rb){
        free(rb);
        rb = NULL;
    }
}


// 重置环形缓冲区
void ring_buffer_reset(RingBuffer *rb){
    rb->full = false;
    rb->head = rb->tail = 0;
}

// 向缓冲区写入数据
bool ring_buffer_push(RingBuffer *rb, uint8_t data){
    if(ring_buffer_is_full(rb))return false;

    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % rb->capacity;
    return true;
}

// 从缓冲区读取数据
bool ring_buffer_pop(RingBuffer *rb, uint8_t *data){
    if(ring_buffer_is_empty(rb))return false;

    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail +1) % rb->capacity;
    return true;
}

// 查看但不移除下一个数据
bool ring_buffer_peek(const RingBuffer *rb, uint8_t *data){
    if(ring_buffer_is_empty(rb))return false;

    *data = rb->buffer[rb->tail];

    return true;
}

// 缓冲区是否为空
bool ring_buffer_is_empty(const RingBuffer *rb){
    return (rb->head == rb->tail);
}

// 缓冲区是否已满
bool ring_buffer_is_full(const RingBuffer *rb){
    return ((rb->head+1) % rb->capacity == rb->tail);
}

// 获取缓冲区可用空间
size_t ring_buffer_available(const RingBuffer *rb){
    return (rb->capacity - (rb->head + rb->capacity - rb->tail)%rb->capacity);
}

// 获取缓冲区已用空间
size_t ring_buffer_size(const RingBuffer *rb){
    return (rb->capacity - ring_buffer_available(rb));
}

// 批量写入数据
size_t ring_buffer_write(RingBuffer *rb, const uint8_t *data, size_t len){
    size_t i = 0;
    while(!ring_buffer_is_full(rb) && i < len){
        ring_buffer_push(rb, data[i]);
        i++;
    }
    return i;
}

// 批量读取数据
size_t ring_buffer_read(RingBuffer *rb, uint8_t *data, size_t len){
    size_t i=0;
    while(!ring_buffer_is_empty(rb) && i < len){
        ring_buffer_pop(rb, &data[i]);
        i++;
    }
    return i;
}
