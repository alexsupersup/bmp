CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=#-lm
OUTPUT=bmp
 
# targets
all: $(OUTPUT)
 
$(OUTPUT): bmp.o main.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) bmp.o main.o $(LDLIBS) -o $(OUTPUT)
 
main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o
 
bmp.o: bmp.c bmp.h
	$(CC) $(CFLAGS) -c bmp.c $(LDLIBS) -o bmp.o
 
# remove compiled files
clean: 
	rm -rf $(OUTPUT) *.o
