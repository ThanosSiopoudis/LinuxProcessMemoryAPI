CC=gcc
CFLAGS= -std=gnu99 -Wall -fpic
LIBRARYFLAGS= -std=gnu99 -shared

debug:clean
	$(CC) -std=gnu99 -g -o processmemoryinterface main.c
	$(CC) $(CFLAGS) -g -c main.c
	$(CC) $(LIBRARYFLAGS) -o libprocessmemoryinterface.1.0.so *.o
stable:clean
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(LIBRARYFLAGS) -o libprocessmemoryinterface.1.0.so *.o
clean:
	rm -vfr *.*o
