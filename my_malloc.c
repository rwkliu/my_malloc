#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

/*
 * my_malloc.c
 *
 * method: 1. check if the free list is available. If not, mmap for memory.
 *         2. search through free list (maybe just created) for free block
 *         3. if nothing found in free list, mmap
 *         block struct
 *         request_memory
 *         find_free_block
 */

typedef struct block {
    int size;
    int is_free;                                  /* 1 for free, 0 for in use */
    struct block *next;
    char data[1];                            /* placeholder for user's memory */
} block_t;

block_t *free_list = NULL;

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
