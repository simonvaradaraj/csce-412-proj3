CC = g++
CFLAGS = -Wall -Werror

main: main.o
	$(CC) $(CFLAGS) -o main.exe main.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp 
	
.PHONY: clean
clean:
	rm -f *.o *.exe