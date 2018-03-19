CC = g++

CFLAGS = -c -Wall

all: jlds

jlds: main.o
	$(CC) main.o -o jlds

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *o *gch jlds
