CC = cc
INCLUDE = datastructure
CFLAGS = -Wall -O3
OBJECTS = datastructure.o
TARGET = demo.bin

demo: $(OBJECTS)
	$(CC) -I$(INCLUDE) $(CFLAGS) $(OBJECTS) demo.c -o $(TARGET)

datastructure.o: $(INCLUDE)/datastructure.c $(INCLUDE)/datastructure.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -rf *.o *.bin *.s
