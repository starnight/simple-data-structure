CC = cc
INCLUDE = .
CFLAGS = -Wall -O3
OBJECTS = datastructure.o
TARGET = demo.bin

demo: $(OBJECTS)
	$(CC) -I$(INCLUDE) $(CFLAGS) $(OBJECTS) demo.c -o $(TARGET)

datastructure.o:
	$(CC) $(CFLAGS) -o $@ -c $(subst .o,.c,$@)

.PHONY: clean
clean:
	rm -rf *.o *.bin *.s
