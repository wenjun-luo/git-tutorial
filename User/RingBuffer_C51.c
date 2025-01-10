//#include <stdio.h>
//#include <stdlib.h>
#include "H/RingBuffer_C51.H"
#include "H/SC92F841x_C.H"

void ringBuffer_init(TagRingBuffer *rb, int size1, char *new_buffer)
{
	// Note: (size-1) is full!!
	if (rb == NULL)
	{
		return;
	}
	rb->buffer = new_buffer;
	if (rb->buffer == NULL)
	{
		return;
	}
	rb->maxCount = size1;
	rb->wrPos = 0;
	rb->rdPos = 0;
	rb->remainCnt = 0;
	return;
}
 
void ringBuffer_free(TagRingBuffer *rb)
{
	if (rb)
	{
		if (rb->buffer)
		{
			free(rb->buffer);
		}
		free(rb);
	}
}
 
int is_ringBuffer_full(TagRingBuffer *rb)
{
	// Note:(MAXCOUNT-1) is full!!
	if (((rb->wrPos) + 1) % (rb->maxCount) == rb->rdPos)
		return 1;
 
	return 0;
}
 
int is_ringBuffer_empty(TagRingBuffer *rb)
{
	if ((rb->wrPos) == rb->rdPos)
	{
		//rb->wrPos = 0;
		//rb->rdPos = 0;
		return 1;
	}
	
	return 0;
}
 
int ringBuffer_pop(TagRingBuffer *rb, char *ch)
{ // read
	if (is_ringBuffer_empty(rb))
	{
		return 0;
	}
	*ch = rb->buffer[rb->rdPos];
	rb->rdPos = (rb->rdPos + 1) % rb->maxCount;
	rb->remainCnt--;
	return 1;
}
 
int ringBuffer_push(TagRingBuffer *rb, char ch)
{ // write
	if (is_ringBuffer_full(rb))
	{
		return 0;
	}
	rb->buffer[rb->wrPos] = ch;
	rb->wrPos = (rb->wrPos + 1) % (rb->maxCount);
	rb->remainCnt++;

	return 1;
}
 
int ringBuffer_getRemainCnt(TagRingBuffer *rb)
{
	return rb->remainCnt;
}
 

