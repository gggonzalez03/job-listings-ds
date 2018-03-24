CC = g++

CFLAGS = -c -Wall

all: jlds

jlds: main.o Job.o
	$(CC) main.o Job.o -o jlds

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Job.o: Job.cpp
		$(CC) $(CFLAGS) Job.cpp

clean:
	rm -rf *o *gch jlds
