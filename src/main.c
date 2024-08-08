#include <stdio.h>
#include <string.h>
#include "my_malloc.h"

int main() {
    char *src = "hello";
    char *dest = my_malloc(strlen(src) + 1);
    
    strcpy(dest, src);
    printf("%s\n", dest);
    return 0;
}