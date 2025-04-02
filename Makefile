CFLAGS = -std=c++11 -g -static
CC = g++
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

compiler.out: $(OBJS)
	$(CC) -o $@ $(OBJS)


main.o: common.h

tokenizer.o: tokenizer.h common.h

test: compiler.out
	./test.sh

clean:
	rm -f program *.o *~ tmp* *.out

.PHONY: test clean