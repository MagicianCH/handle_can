CFLAGS += -Wall
CC = arm-none-linux-gnueabi-gcc


cantest: cantest.o cmd.o
	$(CC) $(CFLAGS) cantest.o cmd.o -o canctrl -g 

cantest.o: cantest.c
	$(CC) -c cantest.c

cmd.o: cmd.c cmd.h
	$(CC) -c cmd.c

.PHONY: clean
clean:
	-rm *.o

