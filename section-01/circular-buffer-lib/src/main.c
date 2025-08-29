//Including our cbuf header file to access our circular buffer library functions
#include "cbuf.h"
#include <stdio.h>

int main(void) 
{ 
	cbuf_t cb;

	if (cbuf_init(&cb, 8) != 0)
	{
		puts("init failed");
		return 1;
	}

	uint8_t data[] = {10,20,30,40,50};
	cbuf_write(&cb, data, 5);
	printf("size after write %zu\n", cbuf_size(&cb));


	uint8_t out[8] = {0};
	size_t n = cbuf_read(&cb, out, 5);
	printf("read %zu bytes: ", n);
	for (size_t i=0;i<n;i++) printf("%u ", out[i]);
        puts("");


	cbuf_free(&cb);
	return 0; 
}
