//including our header file and other headers for working with memory and strings

#include "cbuf.h"
#include <stdlib.h>
#include <string.h>

/*We now have a initalizer function.
We take in a buffer struct with a capacity of integer size.
Then we make sure we aren't declaring a empty buffer.
We then set the size using raw bytes and check for memory allocation errors.
Then we set the size, headers and tails to index 0, and not full
We return a 0 to say that everything went smoothly */

int cbuf_init(cbuf_t *cb, size_t capacity)
{
	if (!cb || capacity == 0) return -1;
	cb->buffer = (uint8_t*)malloc(capacity);
	if (!cb->buffer) return -2;
	cb->capacity = capacity;
	cb->head = cb->tail = 0;
	cb->full = false;
	return 0;
}

/* In this function, we make sure that we don't free a nonexistent buffer.
Once we know a buffer exists, we free it and set it to NULL to avoid dangling pointer.
We then reset the head, tail, and capacity values back to 0 and set full to false.
*/

void cbuf_free(cbuf_t *cb)
{
	if (!cb) return;
	free(cb->buffer);
	cb->buffer = NULL;
	cb->capacity = cb->head = cb->tail = 0;
	cb->full = false;
}

/* This function is a bit similar to the last one.
We do reset the head and tail value back to 0. 
However, in the last function we released the memory, but here we keep it.
*/

void cbuf_reset(cbuf_t *cb)
{
	if (!cb) return;
	cb->head = cb->tail = 0;
	cb->full = false;
}

//Checks if buffer exists and returns if full

bool cbuf_full(const cbuf_t *cb) {return cb && cb-> full;}

//Checks if buffer exists and is empty by seeing if head equals tail

bool cbuf_empty(const cbuf_t *cb) {return cb && !cb->full && cb->head == cb->tail;}

//Checks if buffer exists and how many total elements it can hold

size_t cbuf_capacity(const cbuf_t *cb) {return cb ? cb->capacity : 0;}


/* This next function figures out the number of elements in the circular buffer.
If cb is NULL, then 0. If we have full flag set then its max size.
Otherwise we do head - tail when head is greater than tail.
If wrapped around, we do capacity subtracted from the difference of tail and head.
*/

size_t cbuf_size(const cbuf_t *cb)
{
	if (!cb) return 0;
	if (cb->full) return cb->capacity;
	if (cb->head >= cb->tail) return cb->head - cb->tail;
	return cb->capacity - (cb->tail - cb->head);
}

/* The function uses a pointer to put a byte in the buffer.
Return dalse if the buffer or its memory does not exist.
Write the value at the particular index.
If full, then overwrite by advancing tail to next byte.
Then advance head and set flag as full
*/ 

bool cbuf_put(cbuf_t *cb, uint8_t byte)
{
	if (!cb || !cb->buffer) return false;
	cb->buffer[cb->head] = byte;
	if (cb->full) cb->tail = (cb->tail + 1) % cb->capacity;
	cb->head = (cb->head + 1) % cb->capacity;
	cb->full = (cb->head == cb->tail);
	return true;	
}

/* This function gets the value at the buffer at this particualr index.
It first makes sure the struct, pointer, and value actually exist.
Then it fetches the value itself and sets full to false.
It then moves the tail forward and finds capacity by getting remainder.
Finally, returns a true after the value is fetched.
*/

bool cbuf_get(cbuf_t *cb, uint8_t *out)
{
	if (!cb || !cb->buffer || !out || cbuf_empty(cb)) return false;
	*out = cb->buffer[cb->tail];
	cb->full = false;
	cb->tail = (cb->tail + 1) % cb->capacity;
	return true;
}

/* This next function takes an array of bytes and writes them into buffer one by one.
This is done by using a pointer cb to point to struct, a pointer data to array of bytes and len to show number of bytes written
We then do a safetcy check on buffer struct and make sure our pointer is not at NULL.
Then in the loop we put values and we stop once we reached one below the size to put the correct number of bytes.
*/

size_t cbuf_read(cbuf_t *cb, uint8_t *out, size_t len)
{
	if (!cb || !out) return 0;
	size_t n = 0;
	while (n < len && cbuf_get(cb, &out[n])) n++;
	return n;
}

/* This function lets you look into a function without getting rid of its values. 
First we make sure the struct and pointer exists. We also make sure value is not empty and we reference a actual index in the buffer.
Then we calculate the position using tail and the index we want while accounting for wraparound.
Finally we output our value and return true.*/

bool cbuf_peek(const cbuf_t *cb, size_t index, uint8_t *out)
{
	if (!cb || !out || cbuf_empty(cb) || index >= cbuf_size(cb)) return false;
	size_t pos = (cb->tail + index) % cb->capacity;
	*out = cb->buffer[pos];
	return true;
	
}
	

/* This function writes into a cb buffer with len bytes from data array
If we have no buffer, memory, values, or array, do nothing.
Then we check size of memory we want to write and current buffer space and depending on which is smaller, data can be written or not. 
Then we basically write as much as we can possibly without having overflow in the end of the buffer. 
The next part basically writes the remaining parts left to the beginning of the buffer for the wraparound.
Finally we check flag if head has caughth up to tail and if we wrote something to mark buffer as full.
At last we write the number of successfully written bytes.
*/

size_t cbuf_write(cbuf_t *cb, const uint8_t *data, size_t len)
{
	if (!cb || !cb->buffer || !data || len == 0) return 0;
	
	size_t sz = cbuf_size(cb);
	size_t free_space = cb->capacity - sz;
	size_t to_write = (len < free_space) ? len : free_space;
	if (to_write == 0) return 0;

	size_t head_to_end = cb->capacity - cb->head;
	size_t first = (to_write < head_to_end) ? to_write : head_to_end;

	if (first)
	{
		memcpy(&cb->buffer[cb->head], data, first);
		cb->head = (cb->head + first) % cb->capacity;
	}
	
	size_t remaining = to_write - first;
	if (remaining)
	{
		memcpy(&cb->buffer[cb->head], data + first, remaining);
		cb->head = (cb->head + remaining) % cb->capacity;
	}

	
	cb->full = (cb->head == cb->tail) && (to_write > 0);
	
	return to_write;
}


