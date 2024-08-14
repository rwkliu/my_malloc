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
        current = request_memory(total_size);
        current->size = size;
        current->next = NULL;
        current->is_free = 0;
        free_list = current;
        return (current + 1);
    }

    // Search for a free block
    current = free_list;
    while (current && !(current->is_free && current->size >= size)) {
        prev = current;
        current = current->next;
    }
    // No suitable free block, request more memory
    if (current == NULL) {
        current = request_memory(total_size);
        current->size = size;
        current->next = NULL;
        current->is_free = 0;
        prev->next = current;
        return (current + 1);
    } else {
        // Use the free block
        current->is_free = 0;
    }
    return (current + 1);
}

void *my_calloc(int count, int size) {
    void *ptr = my_malloc(count * size);
    if (ptr != NULL) {
        for (int i = 0; i < count * size; i++)
            ((char*)ptr)[i] = 0;         /* cast as char ptr to fill with 0's */
    }
    return ptr;
}

void *my_realloc(void *ptr, int size) {
    // If ptr is NULL, call malloc for size bytes
    if (ptr == NULL) {
        return my_malloc(size);
    }
    // If there isn't a large enough block, allocate new memory block, copy the 
    //   data pointed to by ptr, free the old allocation, return the pointer to 
    //   the allocated memory
    block_t *block = (block_t *)ptr - 1;
    int ptr_size = block->size;

    if (ptr_size == size) {
        return ptr;
    } else {
        void *new_ptr = my_malloc(size);
        memmove(new_ptr, ptr, size);
        my_free(ptr);
        return new_ptr;
    }
    return NULL;
}

void my_free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    // Get the address of the block from the data pointer, then overwrite the 
    // data memory with a garbage pattern
    block_t *block = (block_t *)ptr - 1;
    memset(ptr, 0xDE, block->size);
    block->is_free = 1;
}

int count_free_list_blocks() {
    block_t *current = free_list;
    int num = 0;

    while (current) {
        num++;
        current = current->next;
    }
    return num;
}

int check_free_blocks() {
    block_t *current = free_list;
    
    while (current) {
        if (current->is_free == 1) {
            printf("block is free\n");
            return 1;
        }
        current = current->next;
    }
    return 0;
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