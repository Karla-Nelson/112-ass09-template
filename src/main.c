/*
 * main.c - Sandbox for testing
 * 
 * To use the functions you implemented in code.c, you must include the header:
 *   #include "code.h"
 *  
 * This tells the compiler where to find the function prototypes.
 * Without this include, the compiler won't know about your functions!
 */

#include <stdio.h>

typedef struct
{

    unsigned char *data; /* heap block of `capacity` bytes */
    size_t size;         /* number of bytes in use (the content) */
    size_t capacity;     /* number of bytes allocated */

} ByteBuffer;

int main(void)
{

    int * r1 = alloc_ints(5);
    int * r2 = alloc_zeroed_ints(3);
    //safe_free((void**)&r1);
    int * r3 = resize_ints(r2, 3, 5);
    int * r4 = duplicate_ints(r2, 3);
    ByteBuffer *buf = buffer_create(2);
    buffer_reserve(buf, 10);
    buffer_append(buf, "G", 1);
    buffer_append_byte(buf, "G");
    buffer_append_string(buf, "Hello");
    int * r5 = buffer_find(buf, "G");
    buffer_insert(buf, 2, "IT", 2);
    buffer_clear(buf);
    buffer_destroy((void**)&buf);

    return 0;
}

// const int n = 12;
//     ByteBuffer buffer1;
//     char *txt = "Hello World"

//     char * temp = malloc(sizeof(char) * (n + 5));
//     memcpy(temp, txt, sizeof(char) * n)