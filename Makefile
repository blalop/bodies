CC = gcc
CFLAGS = -Wall
GTKFLAGS = `pkg-config --cflags --libs gtk+-2.0`

nbody: map.o nbody.o
	$(CC) $(CFLAGS) $^ -o $@ $(GTKFLAGS)

map.o: map.c map.h
	$(CC) $(CFLAGS) -c $< -o $@ $(GTKFLAGS)
	
.PHONY: clean
clean:
	rm -f *.o nbody
