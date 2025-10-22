# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99 -g

# Targets
TARGET = spellcheck
OBJS = spellcheck.o correction.o util.o

# Default target
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

# Object files from source files
spellcheck.o: spellcheck.c correction.h util.h
	$(CC) $(CFLAGS) -c spellcheck.c

correction.o: correction.c correction.h
	$(CC) $(CFLAGS) -c correction.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET) utilTest output.txt

# Unit test build (optional)
utilTest: utilTest.o util.o
	$(CC) -o utilTest utilTest.o util.o

utilTest.o: utilTest.c util.h
	$(CC) $(CFLAGS) -c utilTest.c

.PHONY: clean
