#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

/*
 * my_malloc.c
 *
 * mmap: void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
 */

void *my_malloc(int size)
{
    return mmap(
        0,                        // address
        size,                     // length of mem
        PROT_READ | PROT_WRITE,   // protections
        MAP_ANON | MAP_PRIVATE,   // flags: anonymous: no connection to fd; private: no other proc access
        -1,                       // fd: -1 maps anonymous mem not tied to an fd
        0                         // offset: unneccessary when anonymous mapping into memory
    );

}

int main(void)
{
    char *src = "hello";
    char *dest = my_malloc(strlen(src) + 1);

    strcpy(dest, src);
    printf("%s\n", dest);
    return 0;
}
