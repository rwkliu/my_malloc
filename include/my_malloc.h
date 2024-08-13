#ifndef MALLOC_INCLUDE_H
#define MALLOC_INCLUDE_H

#ifndef BLOCK_STRUCT
#define BLOCK_STRUCT
typedef struct block {
    int size;
    int is_free;
    struct block *next;
} block_t;
#endif

extern block_t *free_list;

block_t *request_memory(int size);
block_t *find_free_block(int size);
void *my_malloc(int size);
void *my_calloc(int count, int size);
void my_free(void *ptr);

#endif