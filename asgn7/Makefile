CC=clang
CFLAGS=-Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
OBJS=bitreader.o bitwriter.o node.o pq.o
HEAD=bitreader.h bitwriter.h node.h pq.h

.PHONY: all clean format scan-build

all: brtest bwtest nodetest pqtest huff dehuff

brtest: brtest.o $(OBJS)
	$(CC) -o brtest brtest.o $(OBJS)

bwtest: bwtest.o $(OBJS)
	$(CC) -o bwtest bwtest.o $(OBJS)

nodetest: nodetest.o $(OBJS)
	$(CC) -o nodetest nodetest.o $(OBJS)

pqtest: pqtest.o $(OBJS)
	$(CC) -o pqtest pqtest.o $(OBJS)

huff: huff.o $(OBJS) dehuff.o
	$(CC) -o huff huff.o $(OBJS)

dehuff: dehuff.o $(OBJS) huff.o
	$(CC) -o dehuff dehuff.o $(OBJS)

%.o: %.c $(HEAD)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f brtest bwtest nodetest pqtest huff dehuff *.o

scan-build: clean
	scan-build --use-cc=clang make

format:
	clang-format -i -style=file *.[ch]
