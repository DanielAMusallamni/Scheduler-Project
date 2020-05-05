CC=gcc
CFLAGS= -ggdb -Wall -pedantic -std=c11


scheduler: scheduler.o queueOps.o ioOps.o printStats.o

scheduler.o: scheduler.c structs.h queueOps.h ioOps.h


queueOps.o: queueOps.c structs.h queueOps.h

ioOps.o: ioOps.c structs.h queueOps.h


printStats.o: printStats.c









clean:
		rm -f *.o scheduler core
