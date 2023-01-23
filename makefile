

CFLAGS+=-Wall -Wextra -std=gnu17 -g -O0


convert: convert.o

clean:
	-rm -f convert.o convert
