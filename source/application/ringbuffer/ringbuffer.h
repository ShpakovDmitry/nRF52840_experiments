/*
 *   file: ringbuffer.h
 * author: ShpakovDmitry
 *   date: 2021-11-16
 */

#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
	uint8_t* buffer;
	size_t head;
	size_t tail;
	size_t max;
	bool full;
} RingBuffer;

typedef RingBuffer* RingBufferHandle;

void RingBuffer_init(  RingBufferHandle rbuff, uint8_t* buffer, size_t size);
void RingBuffer_reset(RingBufferHandle rbuff);
void RingBuffer_put(RingBufferHandle rbuff, uint8_t data);
bool RingBuffer_put2(RingBufferHandle rbuff, uint8_t data);
bool RingBuffer_get(RingBufferHandle rbuff, uint8_t* data);
bool RingBuffer_isEmpty(RingBufferHandle rbuff);
bool RingBuffer_isFull(RingBufferHandle rbuff);
size_t RingBuffer_getCapacity(RingBufferHandle rbuff);
size_t RingBuffer_getSize(RingBufferHandle rbuff);

#endif // RING_BUFFER_H
