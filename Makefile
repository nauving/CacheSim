OBJS = Tokenizer.o parser.o meminstr.o filereader.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)


test : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o test

Tokenizer.o : Tokenizer.cpp Tokenizer.h
	$(CC) $(CFLAGS) Tokenizer.cpp

parser.o : parser.cpp parser.h meminstr.h tokenizer.h
	$(CC) $(CFLAGS) parser.cpp

meminstr.o : meminstr.cpp meminstr.h
	$(CC) $(CFLAGS) meminstr.cpp

filereader : filereader.cpp filereader.h parser.h
	$(CC) $(CFLAGS) filereader.cpp
