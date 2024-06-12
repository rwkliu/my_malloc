#
# Makefile for my_malloc.c
#

CFLAGS = -Wall -Werror -Wextra -g
PROG = my_malloc
OBJS = $(PROG).o

all: $(OBJS)
	cc $(CFLAGS) $(PROG).c -o $(PROG)

my_malloc.o: my_malloc.c
	cc $(CFLAGS) -c $(PROG).c

clean:
	rm -f a.out *.o

fclean: clean
	rm -f $(PROG)
