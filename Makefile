CC=gcc
CFLAGS=-Wall

myavl: myavl.o libavl.o
	$(CC) -o myavl myavl.o libavl.o -I.