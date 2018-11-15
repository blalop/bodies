CC = gcc
CFLAGS = -Wall -Werror -Wfatal-errors -std=c11
CFLAGS_GTK = `pkg-config --cflags --libs gtk+-2.0`

nbody: graphics.o nbody.o bitmap.o
	$(CC) $(CFLAGS) $^ -o $@ $(CFLAGS_GTK)

graphics.o: graphics.c graphics.h
	$(CC) $(CFLAGS) -c $< -o $@ $(CFLAGS_GTK)
	
.PHONY: clean
clean:
	rm -f *.o nbody
