CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = 
EXEC = uniqcounter
HEADERS = item.h ll.h hash.h dictwords.h

all: bench1 bench2 uniqq

$(EXEC): main.o ll.o item.o
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

toy: toy.o ll.o item.o
	$(CC) $^ $(LFLAGS) -o $@

bench1: dictwords_list.o abstractwords.o bench1.o ll.o item.o
	$(CC) $^ $(LFLAGS) -o $@

bench2: dictwords_hash.o abstractwords.o bench2.o hash.o ll.o item.o
	$(CC) $^ $(LFLAGS) -o $@

uniqq: dictwords_hash.o abstractwords.o hash.o ll.o item.o uniqq.o
	$(CC) $^ $(LFLAGS) -o $@

clean:
	rm -rf $(EXEC) *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format
