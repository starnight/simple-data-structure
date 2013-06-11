CC = cc
INCLUDE = .
CFLAGS = -Wall
TARGET = demo.bin

all:
	$(CC) -I$(INCLUDE) $(CFLAGS) *.c -o $(TARGET)

clean:
	rm -rf *.o *.bin *.s
