CC = gcc
CFLAGS = -Wall -g

all: main

main: Main.o StrList.o
	$(CC) $(CFLAGS) Main.o StrList.o -o StrList

Main.o: Main.c 
	gcc $(CFLAGS) -c Main.c

StrList.o: StrList.c StrList.h
	gcc $(CFLAGS) -c StrList.c

clean:
	rm -f *.o main 
