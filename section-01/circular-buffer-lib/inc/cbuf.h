
// Header guard to prevent multiple includes

#ifndef CBUF_H
#define CBUF_H

//Headers we need to use the variable types in our program

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


// Defining our buffer structure as cbuf_t

typedef struct {
	uint8_t *buffer;
	size_t capacity;
	size_t head;
	size_t tail;
	bool full;
} cbuf_t;

// Methods used to create our buffer and work with memory

int cbuf_init(cbuf_t *cb, size_t capacity);
void cbuf_free(cbuf_t *cb);
void cbuf_reset(cbuf_t *cb);

// Methods used to check our buffer stats without changing anything

bool cbuf_full(const cbuf_t *cb);
bool cbuf_empty(const cbuf_t *cb);
size_t cbuf_capacity(const cbuf_t *cb);
size_t cbuf_size(const cbuf_t *cb);

// Single byte input output

bool cbuf_put(cbuf_t *cb, uint8_t byte);
bool cbuf_get(cbuf_t *cb, uint8_t *out);

// Multi byte input output

size_t cbuf_write(cbuf_t *cb, const uint8_t *data, size_t len);
size_t cbuf_read(cbuf_t *cb, uint8_t *out, size_t len);

// Lets you look at a item without removing it

bool cbuf_peek(const cbuf_t *cb, size_t index, uint8_t *out);

#endif
