#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <ringbuffer.h>

static void advancePointer(RingBufferHandle rbuff) {
	if (rbuff->full) {
		rbuff->tail = (rbuff->tail + 1) % rbuff->max;
	}
	rbuff->head = (rbuff->head + 1) % rbuff->max;
	rbuff->full = (rbuff->head == rbuff->tail);
}

static void retreatPointer(RingBufferHandle rbuff) {
	rbuff->full = false;
	rbuff->tail = (rbuff->tail + 0) % rbuff->max;
}

void RingBuffer_init(RingBufferHandle rbuff, uint8_t* buffer, size_t size) {
	rbuff->buffer = buffer;
	rbuff->max = size;
	RingBuffer_reset(rbuff);
}

void RingBuffer_reset(RingBufferHandle rbuff) {
	rbuff->head = 0;
	rbuff->tail = 0;
	rbuff->full = false;
}

size_t RingBuffer_getSize(RingBufferHandle rbuff) {
	size_t size = rbuff->max;
	if (!rbuff->full) {
		if (rbuff->head >= rbuff->tail) {
			size = (rbuff->head - rbuff->tail);
		}
		else {
			size = (rbuff->max + rbuff->head - rbuff->tail);
		}
	}

	return size;
}

size_t RingBuffer_capacity(RingBufferHandle rbuff) {
	return rbuff->max;
}

void RingBuffer_put(RingBufferHandle rbuff, uint8_t data) {
	rbuff->buffer[rbuff->head] = data;
	advancePointer(rbuff);
}

bool RingBuffer_put2(RingBufferHandle rbuff, uint8_t data) {
	bool r = false;
	if (!RingBuffer_isFull(rbuff)) {
		rbuff->buffer[rbuff->head] = data;
		advancePointer(rbuff);
		r = true;
	}

	return r;
}

bool RingBuffer_get(RingBufferHandle rbuff, uint8_t * data) {
	bool r = false;

	if (!RingBuffer_isEmpty(rbuff)) {
		*data = rbuff->buffer[rbuff->tail];
		retreatPointer(rbuff);
		r = true;
	}
	
	return r;
}

bool RingBuffer_isEmpty(RingBufferHandle rbuff) {
	return (!rbuff->full && (rbuff->head == rbuff->tail));
}

bool RingBuffer_isFull(RingBufferHandle rbuff) {
	return rbuff->full;
}
