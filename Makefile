CFLAGS += -Wall
CC = arm-none-linux-gnueabi-gcc


cantest: main.o cmd.o serial.o
	$(CC) $(CFLAGS) main.o cmd.o serial.o -o canctrl -g 

cantest.o: main.c
	$(CC) -c main.c

cmd.o: cmd.c cmd.h
	$(CC) -c cmd.c

serial.o: serial.c serial.h
	$(CC) -c serial.c

.PHONY: clean
clean:
	-rm *.o

