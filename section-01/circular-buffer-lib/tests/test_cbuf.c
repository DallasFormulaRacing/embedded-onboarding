//We include our header files and the following files we need to test the code

#include "cbuf.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>


static void test_init_reset_free(void);
static void test_put_get_basic(void);
static void test_wraparound(void);
static void test_bulk_write_read(void);
static void test_bulk_partial(void);
static void test_peek(void);


/* The basic idea behing this test function is just checking the lifecycle of the buffer.
First we check for initalization and capacity. Then we go ahead and empty the buffer and check the full flag.
Then we go ahead and reset the buffer and check if its actually empty. Finally we free everything to avoid memory leaks.
*/

static void test_init_reset_free(void)
{
	cbuf_t cb;
	assert(cbuf_init(&cb, 8) == 0);
	assert(cbuf_capacity(&cb) == 8);
	assert(cbuf_empty(&cb));
	assert(!cbuf_full(&cb));
	cbuf_reset(&cb);
	assert(cbuf_empty(&cb));
	cbuf_free(&cb);
}

/*This is a implementation of putting things into a buffer.
First we create a buffer with capacity 4 and check if initalization was successful.
Then we insert the values 10 and 20 and check if we actually have 2 items.
Here we are create a value v to test to check that we have the right element.
We first check that we get the value 10 and then 20.
Finally we then empty the buffer and free all memory.
So not only we know the put function works but we get our values in FIFO order.
This matches what we expect from a queue which is the data structure used for buffers.
*/
static void test_put_get_basic(void)
{
	cbuf_t cb; assert(cbuf_init(&cb, 4) == 0);
	assert(cbuf_put(&cb, 10));
	assert(cbuf_put(&cb, 20));
	assert(cbuf_size(&cb) == 2);

	
	uint8_t v = 0;
	assert(cbuf_get(&cb, &v) && v == 10);
	assert(cbuf_get(&cb, &v) && v == 20);
	assert(cbuf_empty(&cb));
	cbuf_free(&cb);		

}

/* Here we are testing if FIFO still holds when we have a wraparound with our buffer. First we initalize our buffer and
put values from 1 to 3. Then we try to see the value at index. We then put values 4 and 5 which force a wrap around. We 
then bulk read 3 values and check to make sure they are correct and in FIFO order. Wr finally free everything.

*/
static void test_wraparound(void) {
    	cbuf_t cb; assert(cbuf_init(&cb, 4) == 0);
    	assert(cbuf_put(&cb, 1));
    	assert(cbuf_put(&cb, 2));
    	assert(cbuf_put(&cb, 3));
    	assert(!cbuf_full(&cb));
    	uint8_t v;
    	assert(cbuf_get(&cb, &v) && v == 1);
    	assert(cbuf_get(&cb, &v) && v == 2);
    	assert(cbuf_put(&cb, 4));
    	assert(cbuf_put(&cb, 5));
    	assert(cbuf_size(&cb) == 3);
    	uint8_t seq[3]; size_t n = cbuf_read(&cb, seq, 3);
    	assert(n == 3 && seq[0]==3 && seq[1]==4 && seq[2]==5);
    	assert(cbuf_empty(&cb));
	cbuf_free(&cb);
}

/* Now we are testing bulk input output of the circular buffer library.
First we create a buffer with size 8 and we make sure it exists.
We then declare a input buffer from 10-60 and a output buffer with 8 0s.
Our cbuf_write function writes the 6 bytes from in onto the buffer.
Then we return the actual number of bytes written to check if it equals 6.
We then try to read 8 bytes out of buffer but only 6 are available.
The out array now contains the same values as the in array.
We then compare the two arrays with memcmp to check if have one to one match.
We then empty the buffer and free up all the memory. 
Once again the FIFO behavior holds. */

static void test_bulk_write_read(void)
{
	cbuf_t cb; assert(cbuf_init(&cb, 8) == 0);
	uint8_t in[] = {10,20,30,40,50,60};
	uint8_t out[8] = {0};
	size_t w = cbuf_write(&cb, in, sizeof in);
	assert(w = sizeof in);
	assert(cbuf_size(&cb) == sizeof in);
	size_t r = cbuf_read(&cb, out, 8);
	assert(r == sizeof in);
	assert(memcmp(in, out, r) == 0);
	assert(cbuf_empty(&cb));
	cbuf_free(&cb);
		
}

/* We first create and test for a circular buffer of size 5. We then try to write 7 bytes into it.
We are trying to see if cbuf_write will stop and and the number of bytes written should only be 5.
We check if only 5 are written and flag reads as full.
Now we try to read in 8 bytes, but since 5 exist, r should still be 5. 
We test again for 5 bytes and check if we have the correct data and we finally free buffer at end.
*/

static void test_bulk_partial(void)
{
	cbuf_t cb; assert(cbuf_init(&cb, 5) == 0);
	uint8_t in[] = {1,2,3,4,5,6,7};
	size_t w = cbuf_write(&cb, in, sizeof in);
	assert(w == 5);
	assert(cbuf_full(&cb) || cbuf_size(&cb) == 5);

	uint8_t out[8] = {0};
	size_t r = cbuf_read(&cb, out, 8);
	assert(r == 5);	
	assert(out[0] == 1 && out[1] == 2 && out[2] == 3 && out[3] == 4 && out[4] == 5);
	cbuf_free(&cb);

}

/* We first make a buffer with capacity 6. We then write 4 values into it. We peek at the first value and see if it 9.
We do the same for the first, second, and third index. Since buffer only has 4 items, peek should fail at 4th index.
We finally clean everything up with free.
*/

static void test_peek(void)
{
	cbuf_t cb; assert(cbuf_init(&cb, 6) == 0);
	uint8_t in[] = {9,8,7,6};
	assert(cbuf_write(&cb, in, 4) == 4);
	uint8_t x = 0;
	assert(cbuf_peek(&cb, 0, &x) && x==9);
    	assert(cbuf_peek(&cb, 1, &x) && x==8);
    	assert(cbuf_peek(&cb, 3, &x) && x==6);
    	assert(!cbuf_peek(&cb, 4, &x));
    	cbuf_free(&cb);
}

// We run all our test functions here.
int main (void)
{
	puts("[cbuf] tests starting...");
 	test_init_reset_free();
    	test_put_get_basic();
    	test_wraparound();
    	test_bulk_write_read();
    	test_bulk_partial();
    	test_peek();
    	puts("[cbuf] all tests passed.");
    	return 0;
}
