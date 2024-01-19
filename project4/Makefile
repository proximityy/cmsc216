CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow -pedantic-errors -fstack-protector-all -Wextra

PROGS = student_tests $(PUBTESTS)

PUBTESTS = public01 public02 public03 public04 public05

.PHONY: all clean backup

all: $(PROGS)

public01: calendar.o public01.o my_memory_checker_216.o
	$(CC) -o $@ calendar.o public01.o my_memory_checker_216.o

public02: calendar.o public02.o my_memory_checker_216.o
	$(CC) -o $@ calendar.o public02.o my_memory_checker_216.o

public03: calendar.o public03.o my_memory_checker_216.o
	$(CC) -o $@ calendar.o public03.o my_memory_checker_216.o

public04: calendar.o public04.o my_memory_checker_216.o
	$(CC) -o $@ calendar.o public04.o my_memory_checker_216.o

public05: calendar.o public05.o my_memory_checker_216.o
	$(CC) -o $@ calendar.o public05.o my_memory_checker_216.o

student_tests: student_tests.o calendar.o my_memory_checker_216.o
	$(CC) -o student_tests student_tests.o calendar.o my_memory_checker_216.o

student_tests.o: student_tests.c event.h calendar.h my_memory_checker_216.h
	$(CC) $(CFLAGS) -c student_tests.c

calendar.o: calendar.c calendar.h
	$(CC) $(CFLAGS) -c calendar.c

my_memory_checker_216.o: my_memory_checker_216.c my_memory_checker_216.h
	$(CC) $(CFLAGS) -c my_memory_checker_216.c

clean: 
	rm -f *.o $(PUBTESTS) a.out

