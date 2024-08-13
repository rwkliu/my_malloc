#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include "my_malloc.h"

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

#define BLOCKSIZE (sizeof(block_t) - sizeof(char[1]))

block_t *free_list = NULL;

block_t *request_memory(int size);

block_t *find_free_block(int size);

void *my_malloc(int size)
{
    block_t *current;
    block_t *prev;
    int total_size = size + BLOCKSIZE;

    if (free_list == NULL) {
        printf("free_list is null\n");
        current = request_memory(total_size);
        current->size = size;
        current->next = NULL;
        current->is_free = 0;
        free_list = current;
        return current->data;
    }

    // Search for a free block
    current = free_list;
    while (current && !(current->is_free && current->size >= size)) {
        printf("Checking through free_list\n");
        prev = current;
        current = current->next;
    }
    // No suitable free block, request more memory
    if (current == NULL) {
        printf("No free block\n");
        current = request_memory(total_size);
        current->size = size;
        current->next = NULL;
        current->is_free = 0;
        return current->data;
    } else {
        // Use the free block
        current->is_free = 0;
    }
    return current->data;
}

void *my_calloc(int count, int size) {
    void *ptr = my_malloc(count * size);
    if (ptr != NULL) {
        for (int i = 0; i < count * size; i++)
            ((char*)ptr)[i] = 0;         /* cast as char ptr to fill with 0's */
    }
    return ptr;
}

void my_free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    // Address of the block from the data pointer
    block_t *block = (block_t *)((char *)ptr - BLOCKSIZE);
    block->is_free = 1;
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

block_t *find_free_block(int size) {
    if (size <= 0) {
        return NULL;
    }
    return NULL;
}