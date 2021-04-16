CFLAGS+=	-Wall -Wextra
CFLAGS+=	-g

all: morse

clean:
	rm -f morse

.PHONY: all clean
