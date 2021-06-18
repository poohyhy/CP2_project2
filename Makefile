CC = gcc
TARGET = tel
OBJECTS = tel.o func.o menu.o

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ -lncurses

clean :
	rm *.o tel