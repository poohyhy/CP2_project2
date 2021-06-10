CC = gcc
CFLAGS = -W -Wall
TARGET = tel
OBJECTS = tel.o func.o menu.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

clean :
	rm *.o tel