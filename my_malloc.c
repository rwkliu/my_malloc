#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

/*
 * my_malloc.c
 *
 * method: store memory pool metadata
 */

typedef struct block {
    int size;
    int is_used;                                  /* 1 for in use, 0 for free */
} block_t;

#define BLOCKSIZE 512

// use static variables for state preservation between calls

void *my_malloc(int size)
{
    if (size == 0)
        return NULL;

    // init free list and meta data list
        // if list is NULL mmap for more memory

    // traverse free list
        // no good free block? mmap for more

}

/*
 * functions to write:
 * - find_free_block
 * - get_chunk
 *      remember to append to end of free_list
 * - split_blocks
 * - merge adjacdent blocks (optional)
 */
