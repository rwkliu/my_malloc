#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_malloc.h"

int main() {
    // Test 1: my_malloc
    char *src = "hello";
    char *dest = my_malloc(strlen(src) + 1);
    strcpy(dest, src);
    printf("dest: %s\n", dest);

    // Test 2: my_malloc
    char *src2 = "goodbye";
    char *dest2 = my_malloc(strlen(src2) + 1);
    strcpy(dest2, src2);
    printf("dest2: %s\n", dest2);

    // Test 3: my_calloc
    char *src3 = "world";
    char *dest3 = my_calloc(1, strlen(src3) + 1);
    strcpy(dest3, src3);
    printf("dest3: %s\n", dest3);

    // Test 4: my_free
    my_free(dest);
    printf("dest after my_free: %s\n", dest);

    // Test 5: Check for the correct number of memory blocks in the free list
    check_free_blocks();
    printf("num blocks: %d\n", count_free_list_blocks());

    return 0;
}