#ifndef _RING_BUFFER_C51_H
#define _RING_BUFFER_C51_H

#include <stdio.h>
#include <stdlib.h>
typedef struct TAG_RING_BUFFER
{
    int wrPos;
    int rdPos;
    int maxCount;
	int remainCnt;
    char *buffer;
	
} TagRingBuffer;
 
void ringBuffer_init(TagRingBuffer *rb, int size, char *new_buffer);
void ringBuffer_free(TagRingBuffer *rb);
int ringBuffer_push(TagRingBuffer *rb, char ch);
int ringBuffer_pop(TagRingBuffer *rb, char *ch);
int ringBuffer_getRemainCnt(TagRingBuffer *rb);


#endif
