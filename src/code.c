#include <stdlib.h>
#include <string.h>
#include "code.h"

/*
 * CSCI 112 Assignment 9 - Dynamic Memory and Memory Functions
 *  
 * Every function below is a skeleton that already compiles. Replace the
 * "// TODO" line (and the "(void)..." lines under it, which only silence
 * "unused parameter" warnings) with your implementation.
 */

/*
 * RULES (read them once, they apply to every function):
 *  - Check the result of every malloc/calloc/realloc. On failure return NULL / false
 *    and leak nothing (free what you already allocated).
 *  - Never write  p = realloc(p, ...);  - use a temporary pointer.
 *  - NULL arguments must never crash your function (see each description).
 *  - Only the standard library: <stdlib.h>, <string.h>, <stdbool.h>, <stddef.h>.
 *  - Compile with:  gcc -g -Wall -Wextra -fsanitize=address,undefined main.c code.c -o main
 */

/* ======================================================================
 * PART 1: Raw dynamic memory (malloc, calloc, realloc, free)
 * ====================================================================== */

/*
 * STEP 1: alloc_ints
 *
 * Allocate room for `count` ints with malloc().
 *  - count == 0 or allocation failure -> return NULL.
 *  - The memory is NOT initialized.
 */

int *alloc_ints(size_t count)
{
    // TODO

    if(count == 0)
    {
        return NULL;
    }

    (void)count;
    

    int * temp = malloc(sizeof(int) * count);

    if(temp == NULL)
    {
        return NULL;
    }

    return temp;

}

/*
 * STEP 2: alloc_zeroed_ints
 *
 * Same as alloc_ints, but every byte of the block must be zero (use calloc()).
 *  - count == 0 or allocation failure -> return NULL.
 */

int *alloc_zeroed_ints(size_t count)
{
    // TODO
    int * temp;

    if(count == 0)
    {
        return NULL;
    }

    (void)count;
    
    temp = (int *)calloc(count, sizeof(int));

    if(temp == NULL)
    {
        return NULL;
    }

    return temp;
}

/*
 * STEP 3: safe_free
 *
 * Receives the ADDRESS of a pointer (usage:  safe_free((void **)&p); ).
 * Free the block that *ptr points to and set *ptr to NULL (nullify!).
 *  - safe_free(NULL) does nothing.
 *  - If *ptr is already NULL, nothing happens.
 *  - Calling it twice on the same pointer must be harmless.
 */

void safe_free(void **ptr)
{
    // TODO
    (void)ptr;

    if(*ptr != NULL)
    {
        free(*ptr);
        *ptr = NULL; 
    }

    else
    {
        return;
    }

}

/*
 * STEP 4: resize_ints
 *
 * Change a block holding `old_count` ints so that it holds `new_count` ints.
 *  - new_count == 0: free arr and return NULL.
 *  - arr == NULL: behave like alloc_zeroed_ints(new_count).
 *  - Otherwise use realloc() through a TEMPORARY pointer. If it fails,
 *    return NULL and leave arr untouched and still valid.
 *  - Old values are kept. If the block grew, the new ints
 *    (old_count ... new_count - 1) must be set to zero with memset().
 *  - Return the (possibly moved) block.
 */

int *resize_ints(int *arr, size_t old_count, size_t new_count)
{
    // TODO
    (void)arr;
    (void)old_count;
    (void)new_count;
    
    if(new_count == 0)
    {
        free(arr);
        return NULL;
    }

    if(arr == NULL)
    {
        return alloc_zeroed_ints(new_count);
    }

    int * temp = realloc(arr, new_count * sizeof(int));

    if(temp == NULL)
    {
        return NULL;
    }

    if(new_count > old_count)
    {
        memset(temp + old_count, 0, sizeof(int) * ((size_t)(new_count - old_count)));
    }

    return temp;



}

/*
 * STEP 5: duplicate_ints
 *
 * Return a NEW block holding a copy of `count` ints from src (malloc + memcpy).
 *  - src == NULL, count == 0 or allocation failure -> return NULL.
 *  - The caller owns the returned block.
 */

int *duplicate_ints(const int *src, size_t count)
{
    // TODO
    (void)src;
    (void)count;

    if (src == NULL || count == 0) 
    {
        return NULL;
    }

    int *dest = malloc(count * sizeof(int));
    
    if (dest == NULL) 
    {
        return NULL;
    }

    memcpy(dest, src, count * sizeof(int));

    return dest;
}

/* ======================================================================
 * PART 2: ByteBuffer - a growing block of bytes
 *
 * Invariants of a valid buffer:
 *   size <= capacity,  capacity >= 1,
 *   every byte of data from index `size` on is 0.
 * ====================================================================== */

/*
 * STEP 6: buffer_create
 *
 * Allocate the struct AND its data block (`capacity` bytes).
 * Fill the data block with zeros (memset), set size = 0.
 *  - capacity == 0 or any allocation failure -> return NULL.
 *  - If the struct was allocated but the data block was not,
 *    FREE THE STRUCT before returning NULL (no leak!).
 */

ByteBuffer *buffer_create(size_t capacity)
{
    // TODO
    (void)capacity;
    
    if (capacity == 0) 
    {
        return NULL;
    }

   
    ByteBuffer *buffer = (ByteBuffer *)malloc(sizeof(ByteBuffer));
    if (buffer == NULL) 
    {
        return NULL;
    }

    buffer->data = (char *)malloc(capacity);

    if (buffer->data == NULL) 
    {
        free(buffer);
        return NULL;
    }

    memset(buffer->data, 0, capacity);

    buffer->size = 0;
    buffer->capacity = capacity;

    return buffer;
}


/*
 * STEP 7: buffer_reserve
 *
 * Make sure the buffer can hold at least `min_capacity` bytes.
 *  - buf == NULL -> false.
 *  - min_capacity <= capacity -> true, nothing changes.
 *  - Otherwise DOUBLE the capacity until it is >= min_capacity
 *    (4 -> 8 -> 16 -> 32 ...), realloc the data (temporary pointer!),
 *    set the new bytes to zero (memset) and update capacity. Return true.
 *  - If realloc fails -> false, the buffer stays unchanged.
 */

bool buffer_reserve(ByteBuffer *buf, size_t min_capacity)
{
    // TODO
    (void)buf;
    (void)min_capacity;
    
    if (buf == NULL) 
    {
        return false;
    }


    if (min_capacity <= buf->capacity) 
    {
        return true;
    }

    size_t new_capacity = buf->capacity;
    
    if (new_capacity == 0) 
    {
        new_capacity = 4; 
    }

    while (new_capacity < min_capacity) 
    {
        new_capacity *= 2;
    }

    int *temp = realloc(buf->data, new_capacity);
    
    if (temp == NULL) 
    {
        return false;
    }

    memset(temp + buf->capacity, 0, new_capacity - buf->capacity);

    buf->data = temp;
    buf->capacity = new_capacity;

    return true;
}

/*
 * STEP 8: buffer_append
 *
 * Append `n` bytes from `data` after the content (memcpy).
 * Grow with buffer_reserve(buf, size + n) if needed.
 *  - buf == NULL, or data == NULL while n > 0 -> false.
 *  - n == 0 -> true, nothing changes.
 *  - On success size grows by n.
 */

bool buffer_append(ByteBuffer *buf, const void *data, size_t n)
{
    // TODO
    (void)buf;
    (void)data;
    (void)n;

    if (n == 0) 
    {
        return true;
    }

    if (buf == NULL || data == NULL) 
    {
        return false;
    }

    
    if (!buffer_reserve(buf, buf->size + n)) 
    {
        return false;
    }

    memcpy(buf->data + buf->size, data, n);

    buf->size += n;

    return true;
    
    
}

/*
 * STEP 9: buffer_append_byte
 *
 * Append one byte. Hint: it is a one-liner using buffer_append().
 */

bool buffer_append_byte(ByteBuffer *buf, unsigned char byte)
{
    // TODO
    (void)buf;
    (void)byte;

    return buffer_append(buf, &byte, 1);
    
}

/*
 * STEP 10: buffer_append_string
 *
 * Append the characters of `str` WITHOUT the terminating '\0'
 * (use strlen() and buffer_append()).
 *  - str == NULL -> false.
 *  - empty string -> true, nothing changes.
 */

bool buffer_append_string(ByteBuffer *buf, const char *str)
{
    // TODO
    (void)buf;
    (void)str;
    
    if (strlen(str) == 0) 
    {
        return true;
    }

    if (buf == NULL || str == NULL) 
    {
        return false;
    }

    
    if (!buffer_reserve(buf, buf->size + strlen(str))) 
    {
        return false;
    }

    memcpy(buf->data + buf->size, str, strlen(str));

    buf->size += strlen(str);

    return true;
}

/*
 * STEP 11: buffer_find
 *
 * Return the index of the FIRST occurrence of `byte` in the CONTENT
 * (bytes 0 ... size-1, never the spare room!). Use memchr().
 *  - not found or buf == NULL -> -1.
 *  - Hint: index = (found pointer) - (start of data).
 */

int buffer_find(const ByteBuffer *buf, unsigned char byte)
{
    // TODO
    (void)buf;
    (void)byte;
    
    if (buf == NULL || buf->data == NULL || buf->size == 0) 
    {
        return -1;
    }

    void *found = memchr(buf->data, byte, buf->size);

    if (found != NULL) 
    {
        return (int)((unsigned char *)found - buf->data);
    }

    return -1;
}


/*
 * STEP 12: buffer_equals
 *
 * true if both buffers have the same size AND the same content bytes
 * (memcmp). Capacities do not matter. Two empty buffers are equal.
 *  - any argument NULL -> false.
 */

bool buffer_equals(const ByteBuffer *a, const ByteBuffer *b)
{
    // TODO
    (void)a;
    (void)b;
    
    if (a == NULL || b == NULL) 
    {
        return false;
    }

    if (a->size == 0 && b->size == 0) 
    {
        return true;
    }

    if (a->size != b->size) 
    {
        return false;
    }

    return memcmp(a->data, b->data, a->size) == 0;
}

/*
 * STEP 13: buffer_insert
 *
 * Insert `n` bytes from `data` so that they start at index `pos`.
 * The old bytes from `pos` on move to the right. pos == size means "append".
 *  - buf == NULL, pos > size, or data == NULL while n > 0 -> false
 *    (buffer unchanged).
 *  - n == 0 -> true, nothing changes.
 *  - Grow with buffer_reserve() if needed.
 *  - The tail moves onto ITSELF (overlap!) -> memmove(), then memcpy()
 *    for the new bytes.
 */

bool buffer_insert(ByteBuffer *buf, size_t pos, const void *data, size_t n)
{
    // TODO
    (void)buf;
    (void)pos;
    (void)data;
    (void)n;
    
    if (buf == NULL) 
    {
        return false;
    }

    if (pos > buf->size) 
    {
        return false;
    }

    if (data == NULL && n > 0) 
    {
        return false;
    }

    if (n == 0) 
    {
        return true;
    }

    if (!buffer_reserve(buf, buf->size + n)) 
    {
        return false;
    }

    // 4. Shift the existing trailing bytes to the right
    // Use memmove because the source and destination regions overlap
    size_t bytes_to_move = buf->size - pos;
    if (bytes_to_move > 0) 
    {
        memmove(buf->data + pos + n, buf->data + pos, bytes_to_move);
    }

    // 5. Copy the new data into the insertion gap
    memcpy(buf->data + pos, data, n);

    // 6. Update the buffer size
    buf->size += n;

    return true;
}

/*
 * STEP 14: buffer_remove
 *
 * Remove `n` bytes starting at index `pos`; the following bytes move left.
 *  - buf == NULL, pos > size or pos + n > size -> false (buffer unchanged).
 *    Write the check so that it cannot overflow:  n > size - pos
 *  - n == 0 -> true, nothing changes.
 *  - Use memmove() for the shift. Afterwards the n bytes that became unused
 *    at the end of the content must be set to zero (memset). Then size -= n.
 */

bool buffer_remove(ByteBuffer *buf, size_t pos, size_t n)
{
    // TODO
    (void)buf;
    (void)pos;
    (void)n;
    
    if (buf == NULL) 
    {
        return false;
    }

    if (pos > buf->size) 
    {
        return false;
    }

    if (pos + n > buf->size) 
    {
        return false;
    }

    if (n > buf->size - pos) 
    {
        return false;
    }

    if (n == 0) 
    {
        return true;
    }

    size_t bytes_to_move = buf->size - (pos + n);
    if (bytes_to_move > 0) 
    {
        memmove(buf->data + pos, buf->data + pos + n, bytes_to_move);
    }

    buf->size -= n;

    memset(buf->data + buf->size, 0, n);

    return true;

}

/*
 * STEP 15: buffer_clear
 *
 * Set size to 0 and zero the WHOLE data block (memset, `capacity` bytes).
 * The capacity stays the same. buf == NULL -> do nothing.
 */

void buffer_clear(ByteBuffer *buf)
{
    // TODO
    (void)buf;

    if(buf == NULL || buf->size == 0 || buf->data == NULL)
    {
        return;
    }

    memset(buf->data, 0, buf->size);

    return true;
}

/*
 * STEP 16: buffer_destroy
 *
 * Receives the ADDRESS of your pointer (usage:  buffer_destroy(&buf); ).
 * Free the data block, then the struct, then set *buf to NULL.
 *  - buf == NULL or *buf == NULL -> do nothing.
 *  - Calling it twice must be harmless.
 */

void buffer_destroy(ByteBuffer **buf)
{
    // TODO
    (void)buf;

    if(*buf != NULL)
    {
        free(*buf);
        *buf = NULL; 
    }

    else
    {
        return;
    }
}

/* ======================================================================
 * PART 3: Deep copies, searching and arrays of strings
 * ====================================================================== */

/*
 * STEP 17: buffer_clone
 *
 * Return a DEEP copy: a new struct with its OWN data block, the same
 * capacity and the same content (memcpy `size` bytes).
 *  - src == NULL or allocation failure -> NULL.
 *  - Changing the clone must never change the source (and vice versa).
 *  - Hint: buffer_create() gives you the new buffer.
 */

ByteBuffer *buffer_clone(const ByteBuffer *src)
{
    // TODO
    (void)src;
    
    if (src == NULL) 
    {
        return NULL;
    }

    
    ByteBuffer *clone = buffer_create(src->capacity);
    if (clone == NULL) 
    {
        return NULL;
    }

    if (src->size > 0 && src->data != NULL) 
    {
        memcpy(clone->data, src->data, src->size);
    }

    clone->size = src->size;

    return clone;
}

/*
 * STEP 18: buffer_concat
 *
 * Return a NEW buffer holding the content of `a` followed by the content of `b`.
 *  - Its capacity is EXACTLY a->size + b->size (but at least 1).
 *  - Neither source is modified.
 *  - Any NULL argument or allocation failure -> NULL.
 *  - Hint: buffer_create() + buffer_append() twice.
 */

ByteBuffer *buffer_concat(const ByteBuffer *a, const ByteBuffer *b)
{
    // TODO
    (void)a;
    (void)b;

    if (a == NULL || b == NULL) {
        return NULL;
    }

    size_t target_capacity = a->size + b->size;
    if (target_capacity == 0) 
    {
        target_capacity = 1;
    }

    // Create the NEW buffer
    ByteBuffer *new_buf = buffer_create(target_capacity);
    if (new_buf == NULL) 
    {
        return NULL;
    }

    if (a->size > 0) 
    {
        if (!buffer_append(new_buf, a->data, a->size)) 
        {
            buffer_free(new_buf);
            return NULL;
        }
    }

    if (b->size > 0) 
    {
        if (!buffer_append(new_buf, b->data, b->size)) 
        {
            buffer_free(new_buf);
            return NULL;
        }
    }

    return new_buf;
}

/*
 * STEP 19: buffer_count
 *
 * Return how many times `byte` occurs in the CONTENT (bytes 0 ... size-1).
 * Use memchr() repeatedly, each time continuing right AFTER the last hit.
 *  - buf == NULL -> 0.
 */

size_t buffer_count(const ByteBuffer *buf, unsigned char byte)
{
    // TODO
    (void)buf;
    (void)byte;
    
    if (buf == NULL || buf->data == NULL || buf->size == 0) 
    {
        return 0;
    }

    size_t count = 0;
    const unsigned char *current_pos = buf->data;
    size_t bytes_remaining = buf->size;

    while (bytes_remaining > 0) 
    {
        const unsigned char *match = memchr(current_pos, byte, bytes_remaining);
        
        if (match == NULL) 
        {
            break;
        }

        count++;
        
        size_t bytes_searched = (size_t)(match - current_pos) + 1;
        current_pos = match + 1;
        bytes_remaining -= bytes_searched;
    }

    return count;
}

/*
 * STEP 20: buffer_shrink_to_fit
 *
 * Reduce the capacity to `size` (but at least 1) using realloc through a
 * TEMPORARY pointer. The content stays.
 *  - buf == NULL -> false.
 *  - Success (also when nothing had to change) -> true.
 *  - realloc fails -> false, buffer unchanged.
 */

bool buffer_shrink_to_fit(ByteBuffer *buf)
{
    // TODO
    (void)buf;
    
    if (buf == NULL) 
    {
        return false;
    }

    size_t target_capacity = buf->size > 0 ? buf->size : 1;

    if (buf->capacity == target_capacity) 
    {
        return true;
    }


    unsigned char *temp = realloc(buf->data, target_capacity);
    if (temp == NULL) 
    {
        return false;
    }

    buf->data = temp;
    buf->capacity = target_capacity;

    return true;
}

/*
 * STEP 21: buffer_split
 *
 * Split the content at every `delim` byte. Return a heap-allocated ARRAY
 * of heap-allocated STRINGS.
 *  - A buffer with k delimiters gives k + 1 tokens. Empty tokens are kept:
 *        "a,bb,,ccc" split at ','  ->  "a", "bb", "", "ccc"
 *        "a,"                      ->  "a", ""
 *        ""   (empty buffer)       ->  exactly ONE empty token ""
 *  - Every token is a separate malloc'ed, '\0'-terminated copy
 *    (memcpy + terminator). Tokens never point into the buffer;
 *    the buffer is not modified.
 *  - The array of pointers must grow while you discover tokens: start small
 *    (for example 4 pointers) and use realloc (doubling).
 *  - Use memchr() to find the delimiters.
 *  - *out_count receives the number of tokens.
 *  - On ANY failure (also buf == NULL or out_count == NULL): return NULL;
 *    if out_count != NULL set *out_count = 0; and FREE everything you
 *    allocated so far.
 */

char **buffer_split(const ByteBuffer *buf, unsigned char delim, size_t *out_count)
{
    // TODO
    (void)buf;
    (void)delim;
    (void)out_count;
    
    if (out_count != NULL) 
    {
        *out_count = 0;
    }
    if (buf == NULL || out_count == NULL) 
    {
        return NULL;
    }

    size_t capacity = 4;
    char **tokens = malloc(capacity * sizeof(char *));
    if (tokens == NULL) 
    {
        return NULL;
    }

    size_t count = 0;
    size_t current_pos = 0;

    while (1) 
    {
        if (count >= capacity) 
        {
            size_t new_capacity = capacity * 2;
            char **new_tokens = realloc(tokens, new_capacity * sizeof(char *));
            if (new_tokens == NULL) {
                goto cleanup;
            }
            tokens = new_tokens;
            capacity = new_capacity;
        }

        unsigned char *start_ptr = (unsigned char *)buf->data + current_pos;
        size_t search_len = buf->size - current_pos;
        unsigned char *delim_ptr = NULL;

        if (search_len > 0) 
        {
            delim_ptr = memchr(start_ptr, delim, search_len);
        }

        size_t token_len = delim_ptr ? (size_t)(delim_ptr - start_ptr) : search_len;

        tokens[count] = malloc(token_len + 1);
        if (tokens[count] == NULL) 
        {
            goto cleanup;
        }

        if (token_len > 0) 
        {
            memcpy(tokens[count], start_ptr, token_len);
        }

        tokens[count][token_len] = '\0';
        count++;

        if (!delim_ptr) 
        {
            break;
        }

        current_pos += token_len + 1;
    }

    *out_count = count;
    return tokens;

cleanup:

    for (size_t i = 0; i < count; i++) 
    {
        free(tokens[i]);
    }

    free(tokens);
    return NULL;
}

/*
 * STEP 22: free_tokens
 *
 * Receives the ADDRESS of your tokens pointer (usage: free_tokens(&tokens, n); ).
 * Free every token first, then the array itself, then set *tokens to NULL.
 *  - tokens == NULL or *tokens == NULL -> do nothing.
 *  - Calling it twice must be harmless.
 */

void free_tokens(char ***tokens, size_t count)
{
    // TODO
    (void)tokens;
    (void)count;

    if (tokens == NULL || *tokens == NULL) 
    {
        return;
    }

    for (size_t i = 0; i < count; i++) 
    {
        free(*tokens[i]);
    }
    
    free(*tokens);

    *tokens = NULL;

}
