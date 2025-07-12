#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "RingBuffer.h"


int main(){
    RingBuffer *buf = ring_buffer_init(10);
    printf("Cur Space :%ld\n",ring_buffer_available(buf));
    for(int i=0;i<99;i++){
        
        ring_buffer_push(buf, i);
        printf("Cur Space :%ld\n",ring_buffer_available(buf));
        if(ring_buffer_is_full(buf))break;
    }

    while(!ring_buffer_is_empty(buf)){
        uint8_t data;
        ring_buffer_pop(buf, &data);
        printf("Cur value = %d\n",data);
    }

    return 0;
}