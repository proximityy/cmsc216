CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all -Wextra

.PHONY: all clean backup

shell_jr: shell_jr.o
	$(CC) -o shell_jr shell_jr.o

shell_jr.o: shell_jr.c
	$(CC) $(CFLAGS) -c shell_jr.c

clean: 
	rm -f *.o a.out

