CC = g++
OPTFLAGS = -O3 
CFLAGS = -c
BIN=cb
READ = src/read_file.cpp src/read_file.h

all	: cb
	@echo -n ""
	rm -f *.o

$(BIN) 	: main.o read_file.o 
	$(CC) $(OPTFLAGS) main.o read_file.o -o cb

main.o : src/main.cpp 
	$(CC) $(CFLAGS)   src/main.cpp
read_file.o : $(READ)
	$(CC) $(CFLAGS)   src/read_file.cpp



clean:
	@rm -f  *.o cb
