CFLAGS = -std=c++11 -g -static
CC = g++
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

compiler.out: $(OBJS)
	$(CC) -o $@ $(OBJS)


main.o: common.h tokenizer.h parser.h code-generator.h

tokenizer.o: common.h tokenizer.h 

parser.o: common.h tokenizer.h parser.h

code-generator.o: common.h parser.h code-generator.h

test: compiler.out
	./test.sh

clean:
	rm -f program *.o *~ tmp* *.out

.PHONY: test clean