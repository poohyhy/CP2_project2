CC = gcc
CFLAGS = -W -Wall -I/usr/local/opt/ncurses/include -L/usr/local/opt/ncurses/lib
TARGET = tel
OBJECTS = tel.o func.o menu.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

clean :
	rm *.o tel