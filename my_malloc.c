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

#define BLOCKSIZE 512

static block_t *free_list = NULL;

block_t *request_memory(int size);

void *my_malloc(int size)
{
    if (size == 0)
        return NULL;

    // init free list and meta data list
        // if list is NULL mmap for more memory

    // traverse free list
        // no good free block? mmap for more

    block = request_memory(size); /* else if block not found, get more memory */
    if (block == NULL)
        return NULL;

    return (void *)block->data;
}

/*
 * purpose: get anonymous memory from OS with mmap and setup first metadata
 *          block
 *    args: size is size of memory that will be mmap-ed. The size of a block
 *          will be added to the size
 *  method: calculate total size of memory wanted, use mmap, check for failure,
 *          then initialize first block in memory.
 *  return: pointer to first block or NULL if mmap fails
 */
block_t *request_memory(int size)
{
    int total_size = sizeof(block_t) + size;
    block_t *block = mmap(
        NULL,                            /* don't start at a specific address */
        total_size,                           /* length of the memory desired */
        PROT_READ | PROT_WRITE,                 /* memory protections desired */
        MAP_ANONYMOUS | MAP_PRIVATE,/* ANON: no fd; PRIVATE: no other proc access */
        -1,                            /* fd: -1 means not tied to certain fd */
        0                                                        /* no offset */
    );
    if (block == NULL)
        return NULL;

    block->size = size;
    block->is_free = 0;
    block->next = NULL;

    return block;
}
