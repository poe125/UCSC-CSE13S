CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = 
EXEC = xd

all: $(EXEC)

$(EXEC): $(EXEC).o xd.o
	$(CC) $^ -o $@ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format
