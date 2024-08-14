#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_malloc.h"

int main() {
    char *src = "hello";
    char *dest = my_malloc(strlen(src) + 1);
    strcpy(dest, src);
    printf("dest: %s\n", dest);

    char *src2 = "goodbye";
    char *dest2 = my_malloc(strlen(src2) + 1);
    strcpy(dest2, src2);
    printf("dest2: %s\n", dest2);

    char *src3 = "world";
    char *dest3 = my_calloc(1, strlen(src3) + 1);
    strcpy(dest3, src3);
    printf("dest3: %s\n", dest3);

    my_free(dest);
    printf("dest after my_free: %s\n", dest);

    check_free_blocks();

    return 0;
}