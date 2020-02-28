CC = g++
OPTFLAGS =  -O3 -std=c++11 -Wall
CFLAGS = -c
BIN=cb
READ = src/read_file.cpp src/read_file.h

all	: cb
	@echo -n ""
	rm -f *.o

$(BIN) 	: main.o udir.o dir.o
	$(CC) $(OPTFLAGS) main.o udir.o dir.o -o cb

main.o : src/main.cpp 
	$(CC) $(CFLAGS)   src/main.cpp
udir.o : src/udir.cpp src/udir.h
	$(CC) $(CFLAGS) -std=c++11  src/udir.cpp
dir.o : src/dir.cpp src/dir.h
	$(CC) $(CFLAGS) -std=c++11   src/dir.cpp




clean:
	@rm -f  *.o cb
