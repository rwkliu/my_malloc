#ifndef MALLOC_INCLUDE_H
#define MALLOC_INCLUDE_H
#include <stddef.h>
typedef struct block {
    size_t size;
    int free;
    struct block *left;
    struct block *right;
    char data[];
}   block_t;
#endif