CFLAGS+=	-Wall -Wextra

all: morse morse-pwmplay

clean:
	rm -f morse morse-pwmplay

.PHONY: all clean
