#include <stdio.h>
#include <string.h>
#include "my_malloc.h"

int main() {
    char *src = "hello";
    char *dest = my_malloc(strlen(src) + 1);
    char *src2 = "goodbye";
    char *dest2 = my_malloc(strlen(src2) + 1);
    
    strcpy(dest, src);
    strcpy(dest2, src2);
    printf("dest: %s\n", dest);
    printf("dest2: %s\n", dest2);
    return 0;
}